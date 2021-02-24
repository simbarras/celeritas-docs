<!--
Generate to latex:
```
$ pandoc -o code-arch.tex -r gfm code-arch.md
```
-->
## Code architecture

In the short term, Celeritas is designed as a standalone application that
transport particles exclusively on device. To support robust and rapid unit
testing, its components are designed to run natively in C++ on traditional
CPUs regardless of whether CUDA is available for on-device execution.

Like other GPU-enabled Monte Carlo transport codes such as Shift, the low-level
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

## Data model

Software for heterogeneous architectures must manage independent
*memory spaces*. _Host_ allocations use `malloc` or
standard C++ library memory management, and the allocated data is accessible
only on the CPU. _Device_ memory is allocated with `cudaMalloc` and is
generally available only on the GPU. The CUDA Unified Virtual Memory
feature allows CUDA-allocated memory to be automatically paged between host and
device with a concomitant loss in performance. The Kokkos performance
portability layer [cite] manages the allocation of memory and transfer of data
between host and device using a class `Kokkos::View<T, MemorySpace>` which can
act like a `std::shared_pointer` (it is reference counted), a `std::vector` (it
allocates and manages memory), and a `std::span` (it can also provide a
non-owning view to stored data). A similar class has been developed for
Celeritas but with the design goal of supporting the deeply hierarchical data
needed for tabulated physics data (in contrast to Kokkos' focus on dense linear
algebraic data).

The `celeritas::Pie` (XXX please rename this) class manages data allocation and
transfer between CPU and GPU with primary design goal of constructing deeply
hierarchical data on host at setup time and seamlessly copying to device.

 String  | Particle | Description
----- | ----- | -----
`std::vector<char>` | `Pie<ParticleState, value>` | Manages/owns data
`std::span<char>` | `Pie<ParticleState, reference>` | Low level access to the raw data
`std::span<const char>` | `Pie<ParticleState, const_reference>` | Low level access to the raw data
`std::string_view` | `ParticleView` | High level operation on the data

The Celeritas data model separates persistent data from state data.
Calculating the Lorentz factor $\gamma$ of a particle requires both the rest
mass $mc^2$---which is constant for all particles of the same type but is not a
fundamental constant nor the same for all particles---and the kinetic energy
$K$. It is a parameterized expression $\gamma(m;K) = 1 + \frac{K}{mc^2}$.
Celeritas differentiates from shared data such as $m$ (parameters, shortened to
`Params`) from state data particular to a single track such as energy or
particle type (`State`).

In Celeritas, a particle track is not a single object nor a struct of arrays.
Instead, sets of classes (Params plus State) define aspects of a track

