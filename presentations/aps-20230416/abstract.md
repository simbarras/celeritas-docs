# An overview of Celeritas: a novel GPU Monte Carlo detector simulation code

The next-generation of High Energy Physics (HEP) experiments will rely on a vast
increase in detector complexity and data collection, leading to an unprecedented
amount of computing storage and processing capacity needs. Contemporary
increases in computing capacity are primarily due to the use of heterogeneous
architectures that rely on the high performance-per-Watt of GPUs. Celeritas, a
new GPU-optimized detector simulation code, seeks to unlock the resources of
DOE’s Leadership Computing Facilities (LCFs) and the next generation of
computing grid hardware for HEP experiments. Early results show a 40× speedup
factor for standalone EM simulations on LCF computers when using GPUs. This talk
will provide an overview of Celeritas, focusing on its physics capabilities and
integration with the CPU-based detector simulation code Geant4. Current
Celeritas’ electromagnetic (EM) physics models for electrons, positrons, and
photons will be verified against Geant4, with an additional verification for
coupled offloading, where Geant4 processes hadronic and decay physics but sends
EM particles to Celeritas, with an estimated speedup of 2–3× compared to a
Geant4-only run. The presentation will also preview future plans for integration
with HEP experiments, of which EM offloading is the first step.
