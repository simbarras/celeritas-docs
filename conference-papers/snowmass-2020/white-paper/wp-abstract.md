# Celeritas---a GPU detector simulation code

- T.M. Evans, S.R. Johnson, S.C. Tognini (ORNL)
- P. Romano, A. Lund (ANL)
- P. Canal, S.Y. Jun, G. Lima, V.D. Elvira, K.L. Genser (FNAL)
- V.R. Pascuzzi (BNL)

- - -

Within the next decade, experimental HEP will enter a new era of scientific
discovery through a set of targeted programs recommended by the Particle
Physics Project Prioritization Panel (P5). The two main ones are the upcoming
High Luminosity LHC (HL-LHC), including the upgrade of its four main
experiments, along with the Deep Underground Neutrino Experiment (DUNE). These
two efforts will require an unprecedented amount of computational capacity and
face complex challenges in every computational front, demanding advancements in
signal processing, data management, Monte Carlo (MC), reconstruction, and
analysis techniques. In order to alleviate one of the impending computational
bottlenecks that both the Energy and Intensity Frontiers are expected to face,
we present _Celeritas_, an Exascale MC particle transport code.
_Celeritas_ is designed to leverage the vast computing power of DOE's
Leadership Computing Facilities (LCFs) while maintaining similar physics
capabilities currently available in Geant4.
As it targets scalability and compatibility with the
different heterogeneous architectures that will form the network of LCFs over
the next decade, it is not expected to replace Geant4, but will serve as a
highly specialized MC extension that will be orders of magnitude faster when
run on LCFs. This paper presents the planned roadmap for _Celeritas_,
including its proposed code architecture, physics capabilities, and strategies
for integrating it on existing and future experimental HEP computing workflows.
