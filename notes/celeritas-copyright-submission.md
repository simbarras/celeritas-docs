# Celeritas Copyright submission

```
Amanda Lund <alund@anl.gov> / 9700 S. Cass Avenue Lemont, IL 60439 /  Argonne National Laboratory
Ben Morgan <ben.morgan@warwick.ac.uk> / Coventry CV4 7AL, UK / University of Warwick
Doaa Deeb <doaadeeb@berkeley.edu> / One Shields Avenue, Davis, CA 95616 / University of California, Davis
Guilherme Lima <lima@fnal.gov> / PO Box 500, Batavia, IL 60510-5011 / Fermilab
Paul Romano <promano@anl.gov> / 9700 S. Cass Avenue, Lemont, IL 60439 /  Argonne National Laboratory
Philippe Canal <pcanal@fnal.gov> / PO Box 500, Batavia, IL 60510-5011 / Fermilab
Soon Yung Jun <syjun@fnal.gov> / PO Box 500, Batavia, IL 60510-5011 / Fermilab
Vincent R Pascuzzi <vrpascuzzi@bnl.gov> / 1 Cyclotron Road, Berkeley, CA 94720-8235 / Lawrence Berkeley Lab
Stefano C Tognini <togninis@ornl.gov> / 1 Bethel Valley Rd, Oak Ridge, TN 37831 / Oak Ridge National Laboratory
```

# Problem that was solved

In order to interpret the results from the complex CMS and ATLAS detectors used
by the Large Hadron Collider (LHC), analysts must execute numerous
computationally expensive Monte Carlo simulations of the detector response to
hypothetical physics reactions. These simulations currently rely on the Geant4
detector simulation software that only runs on CPUs, but computational centers
are increasingly reliant on GPUs for the bulk of numerical processing power.
New particle transport algorithms and physics implementations are necessary to
adapt detector simulations to the present-day high performance computational
hardware which will be the standard computational hardware of the future.

# Solution provided by the computer code

Celeritas is a novel code that implements Monte Carlo particle transport for
high-energy physics detectors simulations. The primary innovation is the
development of algorithms and code layout compatible with GPU offloading, which
is currently implemented with CUDA, HIP, and OpenMP.

# Computer code’s functionality

Celeritas currently supports on-GPU simulation of EM particle showers. It
currently implements standard EM physics, including multiple scattering and
energy loss fluctuations. The code supports propagation through magnetic fields
with user-implemented field types. Geometry support is provided through VecGeom
for GDML (Geant4 detector description) navigation, and ORANGE (Oak Ridge
Advanced Nested Geometry Engine) for testing and experimentation.  Celeritas
performs particle transport on GPUs using the CUDA and HIP libraries, and can
also transport (primarily for testing) on CPUs with optional OpenMP for
multithreading support.

# Advantages / Benefits

Celeritas has a 50% performance advantage on CPU compared to Geant4
for select problems, and a factor-of-forty performance advantage on Summit,
where the GPUs account for the bulk of processing power.

# Multiplatform

Celeritas is targeted at LCF supercomputers but also tested and performant on personal computers (laptops) and smaller clusters (for grid computing).

# DOE sponsor

DOE ASCR / Christine Chalk / christine.chalk@science.doe.gov / 301-903-5152

