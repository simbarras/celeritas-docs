<!--  -*- coding: utf-8 -*- -->
<!--
Generate to latex:
```
$ pandoc -o code-arch.tex -r gfm+tex_math_dollars code-arch.md
```
-->
# Code Architecture

In the short term, Celeritas is designed as a standalone application that
transport particles exclusively on device. To support robust and rapid unit
testing, its components are designed to run natively in C++ on traditional
CPUs regardless of whether CUDA is available for on-device execution.

Like other GPU-enabled [MC] transport codes such as Shift [pandya_implementation_2016,hamilton_continuous-energy_2019], the low-level
component code used by transport kernels is designed so that each particle
track corresponds to a single thread, since particle tracks once created are
independent of each other. There is therefore essentially no cooperation
between individual threads, facilitating the dual host/device annotation of
most of Celeritas. The allocation of secondary particles and the initialization
of new tracks from these secondaries both require CUDA-specific programming,
but those components are encapsulated so that both host and device code
can safely construct secondaries.

To support parallelizing our initial development over several team members, and
to facilitate refactoring and performance testing of code, Celeritas uses a
highly modular programming approach based on composition rather than
inheritance. As much as possible, each major code component is built of
numerous smaller components and interfaces with as few other components as
possible.

As an example of the granularity of classes, consider the sampling of
secondaries from a model. In contrast to the virtual
`G4VModel::sample_secondaries` member function in Geant4, each model in
Celeritas defines an independent function-like object for sampling secondaries.
Each `Interactor` class is analogous a C++ standard library "distribution": the
distribution parameters (including particle properties, incident particle
energy, and incident direction) are class construction arguments, and the
function-like `Interactor::operator()` takes as its sole input a random number
generator and returns an `Interaction` object, which encodes the change in
state to the particle and the secondaries produced.

## Data model

Software for heterogeneous architectures must manage independent
*memory spaces*. _Host_ allocations use `malloc` or
standard C++ library memory management, and the allocated data is accessible
only on the CPU. _Device_ memory is allocated with `cudaMalloc` and is
generally available only on the GPU. The CUDA Unified Virtual Memory
feature allows CUDA-allocated memory to be automatically paged between host and
device with a concomitant loss in performance. Another solution to memory space
management is a portability layer such as Kokkos [cite], which manages the
allocation of memory and transfer of data
between host and device using a class `Kokkos::View<class, MemorySpace>` which
can
act like a `std::shared_pointer` (it is reference counted), a `std::vector` (it
allocates and manages memory), and a `std::span` (it can also provide a
non-owning view to stored data). A similar class has been developed for
Celeritas but with the design goal of supporting the deeply hierarchical data
needed for tabulated physics data (in contrast to Kokkos' focus on dense linear
algebraic data).

The `celeritas::Collection<class, Ownership, MemSpace>` class manages data
allocation and transfer between CPU and GPU with the primary design goal of
constructing deeply hierarchical data on host at setup time and seamlessly
copying to device. The templated `class` must be trivially copyable --
either a fundamental data type or a struct of such types. An individual item
in a collection can be accessed `ItemId<class>`, which is a trivially copyable
but type-safe index; and a range of items (returned as a `Span<class>`) can be
accessed with a trivially copyable `ItemRange<class>`, which is a
container-like slice object containing start and stop indices. Since
`ItemRange` is trivially copyable and `Collection`s have the same data layout
on host and device, a set of Collections that reference data in each other
provide an effective, efficient, and type-safe means of managing complex
hierarchical data on host and device.

As an example, consider material definitions (omitting isotopics for
simplicity), which contain three levels of indirection: an array of materials has
an array of pointers to elements and their fractions in that material. In
a traditional C++ code this could be represented as `vector<vector<pair<Element*,
double>>>` with a separately allocated `vector<Element>`. With helper
libraries such as Thrust [cite] there is no direct CUDA analog to this
structure because device memory management is limited to host code. Celeritas
chooses not to use in-kernel `cudaMalloc` calls for performance and
portability considerations. Instead, Celeritas represents the nested hierarchy
as a set of `Collection` objects bound together as a `MaterialParamsData`
struct.
```c++
struct Element
{
    int            atomic_number;
    units::AmuMass atomic_mass;
};

struct MatElementComponent
{
    ItemId<Element> element;
    real_type       fraction;
};

struct Material
{
    real_type   number_density;
    real_type   temperature;
    MatterState matter_state;
    ItemRange<MatElementComponent> components;
};

template<Ownership W, MemSpace M>
struct MaterialParamsData
{
    template<class T>
    using Items = celeritas::Collection<T, W, M>;

    Items<Element>             elements;
    Items<MatElementComponent> elcomponents;
    Items<Material>            materials;
    unsigned int               max_elcomponents;

    template<Ownership W2, MemSpace M2>
    MaterialParamsData& operator=(const MaterialParamsData<W2, M2>& other);
};
```
A `MaterialParamsData<Ownership::value, MemSpace::host>` is constructed
incrementally on the host (each `Items<class>` in that template instantiation
is a thin wrapper to a `std::vector`), then copied to a
`MaterialParamsData<Ownership::value, MemSpace::device>` (where each
`Items<class>` is a separately managed `cudaMalloc` allocation) using the
templated assignment operator. The definition of that operator simply
assigns each element from the `other` instance. For primitive data such as
`max_elcomponents`, the value is simply copied; for `Items` the templated
`Collection::operator=` performs a host-to-device transfer under the hood.

To access the data on device, a `MaterialParamsData<Ownership::const_reference,
MemSpace::device>` (where each `Items<class>` is a `Span<class>` pointing to
device memory) is constructed using the sample assignment operator from
the `<value, device>` instance of the data. The `const_reference` and
`reference` instances of a Collection are trivially copyable and can be passed
as kernel arguments or saved to global memory.

The first material in a `MaterialParamsData<Ownership::const_reference,
MemSpace::device> data` instance can be accessed as:
```c++
const Material& m = data.materials[ItemId<Material>(1)];
```
A view of its elemental component data is:
```c++
Span<const MatElementComponent> els = data.elcomponents[material.components];
```
And the elemental properties of the first constituent of the material are:
```c++
const Element& el = data.elements[data.element];
```

In practice, the `MaterialParamsData` itself is an implementation detail
constructed by the host-only class `MaterialParams` and used by the
device-compatible class `MaterialView` and `ElementView`, which encapsulate
access to the material and element data. In Celeritas, `View` objects are to
`Collection` as `std::string_view` is to `std::vector<char>`.

## States and parameters

The Celeritas data model is careful to separate persistent shared "parameter"
data from dynamic local "state" data, as there will generally one independent
state per GPU thread.
To illustrate the difference between parameters and states, consider the
calculation of the Lorentz factor $\gamma$ of a particle, which is a function
of both the rest mass $mc^2$—which is constant for all particles of the same
type but is not a fundamental constant nor the same for all particles—and the
kinetic energy $K$.
It is a parameterized expression $\gamma(m;K) = 1 + \frac{K}{mc^2}$.
Celeritas differentiates from shared data such as $m$ (parameters, shortened to
`Params`) from state data particular to a single track such as kinetic energy
$K$ or particle type (`State`).
Inside transport kernels, the `ParticleTrackView` class combines the parameter
and state data with the local GPU thread ID to encapsulate the fundamental
properties of a track's particle properties -- its rest mass, charge, and
kinetic energy, as well as derivative properties such the magnitude of its
relativistic momentum.

In Celeritas, a particle track is not a single object nor a struct of arrays.
Instead, sets of classes (Params plus State) define aspects of a track, each
of which is accessed through a `TrackView` class. Table
XXX shows the current track attributes independently implemented in Celeritas.

Module | State | Params
---- | ----- | -----
Particle | Kinetic energy and particle ID | Properties for each particle type
Material | Current material ID | Material densities, elements, etc.
Geometry | Position, direction, volume ID | Geometry description
Sim | Track ID, Event ID, time | —
Physics | Distance to interaction,  | Models, processes,
        |  cached cross sections | cross section tables

## On-device allocation

One requirement for transporting particles in electromagnetic showers is
the efficient allocation and construction of secondary particles. The number of
secondaries produced during an interaction varies according to the physics
process, random number generation, and other properties. This implies a
large variance in the number of secondaries produced from potentially millions
of tracks undergoing interactions in parallel on the GPU.

To enable runtime dynamic allocation of secondary particles, we have authored a
function-like `StackAllocator<class>` templated class that uses a large
on-device allocated array with a fixed capacity along with an atomic addition
to unambiguously reserve one or more items in the array. The call argument to a
`StackAllocator` takes as an argument the number of elements to
allocate, and if allocation is successful, it uses placement new to
default-initialize each element and returns a pointer to the first element. If
the capacity is exceeded during the allocation (or by a parallel thread also in
the process of allocating), a null pointer is returned.

```c++
template<class T>
CELER_FUNCTION auto StackAllocator<T>::operator()(size_type count)
    -> result_type
{
    // Atomic add 'count' to the size pointer which resides in global memory
    size_type start = atomic_add(data_.size, count);
    if (CELER_UNLIKELY(start + count > data_.storage.size()))
    {
        // Out of memory: restore the old value so that another thread can
        // potentially use it. Multiple threads are likely to exceed the
        // capacity simultaneously. Only one has a "start" value less than or
        // equal to the total capacity: the remainder are (arbitrarily) higher
        // than that.
        if (start <= data_.storage.size())
        {
            // We were the first thread to exceed capacity, even though other
            // threads might have failed (and might still be failing) to
            // allocate. Restore the actual allocated size to the start value.
            // This might allow another thread with a smaller allocation to
            // succeed, but it also guarantees that at the end of the kernel,
            // the size reflects the actual capacity.
            *data_.size = start;
        }

        // Return null pointer, indicating failure to allocate.
        return nullptr;
    }

    // Initialize the data at the newly "allocated" address
    value_type* result = new (data_.storage.data() + start) value_type;
    for (size_type i = 1; i < count; ++i)
    {
        // Initialize remaining values
        new (data_.storage.data() + start + i) value_type;
    }
    return result;
}
```
In the above code, `CELER_FUNCTION` is preprocessed to `__host__ __device__`
when run through CUDA, and `CELER_UNLIKELY` is a compiler optimization hint
that the enclosed condition is possible but rare.

To accommodate large numbers of secondaries on potentially limited GPU memory,
we define a `Secondary` class that carries the minimal amount of information
needed to reconstruct it from the parent track, rather than as a full-fledged
track:
```c++
struct Secondary
{
    ParticleId       particle_id{};
    units::MevEnergy energy{zero_quantity()};
    Real3            direction;

    explicit inline CELER_FUNCTION operator bool() const;
};
```

The final aspect of GPU-based secondary allocation is how to gracefully handle
an out-of-memory condition without crashing the simulation *or* invalidating
its reproducibility. This can be accomplished by ensuring that no random
numbers are sampled before allocating storage for the secondaries, and by
adding a external loop over the interaction kernel to reallocate extra
secondary space or process secondaries so that all interactions can
successfully complete in the exceptional case where the secondary storage space
is exceeded.

[FIG: interaction-secondaries]
