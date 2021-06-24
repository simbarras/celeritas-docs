The objective of Celeritas is to provide full-fidelity, fast standard model
particle transport for LHC detector simulations using next-generation HPC
computer hardware. This capability is needed because current high-fidelity,
time-dependent, detector simulations will not scale to the proposed $10\times$
LHC luminosity increase in the 2027 time frame. The technical capabilities
needed to achieve breakthroughs in this area are to efficiently use leadership
class hardware based on GPUs to increase particle tracking throughput with
concurrent improvements in I/O and post-processing analysis.  Celeritas builds
on demonstrated GPU performance gains achieved through the ECP ExaSMR project
Monte Carlo neutron transport codes[^1] and the associated software technology
libraries delivered in ECP's E4S software stack[^2].

To meet the primary objective, Celeritas has a two-pronged approach for
incorporation into existing LHC detector simulation workflows: (1) use
Celeritas to offload electromagnetic (EM) physics in a standard Geant4
constructed application and (2) use Celeritas as part of a broader LHC
workflow for complete LHC detector simulations including hadronic (proton)
physics.  Our proposed 6-year plan, building on the successful initial
application demonstration work that was performed 2021, is as follows:

Table 1: Celeritas milestones

-------------------------------------------------------------
Year   Principal milestone
----   ------------------------------------------------------
2022   Integration with detector post-processing workflows

2023   Complete EM physics

2024   EM physics integration into experimental workflows
       through Geant4

2025   Validation of EM physics

2026   Hadronic physics for LHC energy frontiers experiments

2027   Validation of LHC detector simulation physics

2028+  Transition to operations

-------------------------------------------------------------

The technical approach in Celeritas is to extend the algorithms described in
Hamilton and Evans, 2019[^1] for neutron Monte Carlo particle transport on
GPUs to the complete standard model particle suite currently supported by
Geant4 to support LHC detector simulations. We have demonstrated significant
progress in this area as summarized in Johnson et al., 2021[^3], in which the
core classes and design patterns that facilitate development of an efficient,
GPU-enabled particle transport code for high energy physics are described.  We
have compiled initial results from a simple but nontrivial GPU physics
simulation incorporating Klein-Nishina scattering with secondary electron
production that showed an "unoptimized" factor of about $160\times$
performance improvement over a single-CPU version of the same simulation with
identical underpinning components. Using the Celeritas architecture, we have
independently examined a set of potential optimizations that cumulatively
boosted the speedup to about $220\times$.

Naturally, the complexity of a complete EM physics simulation will require
additional GPU kernels, thus the full applications is expected to to have a
smaller speedup than this mini-app.  However, the ease of implementing and
testing each change promises that the infrastructure in place will enable
similar optimizations in the future full-featured physics application.

The next phase of Celeritas development will be the incorporation of a
complete EM physics transport loop in the presence of external magnetic fields
with secondary particle production and transport. This capability will provide
the basis upon which the milestones listed in Table 1 will be completed.
Future work will present the design choices made to enable these additional
features, as well as more CPU comparisons and GPU performance analysis.

[^1]: S. P. Hamilton and T. M. Evans, “Continuous-energy Monte Carlo neutron
transport on GPUs in the Shift code,” Annals of Nuclear Energy, vol. 128,
pp. 236–247, Jun. 2019, doi: 10.1016/j.anucene.2019.01.012.

[^2]: https://e4s-project.github.io

[^3]: S.R. Johnson, S.C. Tognini, P. Canal, T. Evans, S.Y. Jun, G. Lima,
A. Lund, and V.R. Pascuzzi.  "Novel features and GPU performance analysis for
EM particle transport in the Celeritas code," vCHEP 2021, 17-21 May, 2021.
