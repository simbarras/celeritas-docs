# July 2021 -- June 2022

## Prototype performance portability

Celeritas currently requires CUDA, but imminent DOE computing facilities will
use GPU hardware from other vendors (AMD, Intel) which would require different
heterogeneous programming models.
- Determine which platforms are needed for HEP at scale.
- Investigate and implement a prototype of Celeritas in a performance
  portability model such HIP, SYCL, or Kokkos.
- Determine implications for VecGeom, which has strong implementation dependence
  on CUDA-specific features.

## Complete standard EM physics

Implement the full-featured but not necessarily validated set of "standard EM
physics" models in Celeritas on GPU.
- Multiple scattering
- Spatially dependent magnetic fields.

## Prototype integration with experiment frameworks

Add initial capabilities for interacting with experiment frameworks, possibly
including:
- Multithread support
- Client-defined scoring regions
- Detector output

# July 2021 -- June 2022

## Validate standard EM physics

Complete a series of benchmark tests, with and without CMS geometry, to
validate the Celeritas implementation of standard EM physics.

## Baseline EM physics runtime performance

Establish a baseline performance of Celeritas on EM shower physics. Explore
performance/accuracy tradeoffs from using single-precision math in the code.

## Integrate with Geant4

Implement a plugin "Acceleritas" that uses the new tasking model in Geant4 to
dispatch EM particles to the Celeritas GPU physics solvers.

# July 2022 -- June 2023

## Expand physics capabilities

Integrate new physics (e.g., hadrons) into Celeritas to support experimental
campaigns.

## Demonstrate full event simulation

Show that Celeritas can effectively simulate entire particle showers from
initiating events.

## Explore integration with other HEP applications

The ability to rapidly model immense numbers of particles may have implications
besides direct high-fidelity simulation. Support external CHEP efforts to
develop "fast" simulations via machine learning by generating on-the-fly
"training" data with Celeritas.
