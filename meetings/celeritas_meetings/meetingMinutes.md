
Meeting minutes
===============

# Fri Mar 20, 2020

Tom presented current budget situation.
FWP is in process and the current document is on Celeritas' General Slack channel.

Seth described the two milestones for current FWP:

- VecGeom GPU verification
- GPU performance demonstration of EM physics using a gdml geometry

Seth started a Rosetta Stone for nomenclature between Nuclear and HEP physics to
avoid confusion as we move forward. File is available on GitHub.

Krzysztof suggested talking to Soon Yung about CMS MC. Stefano will work on it.

FNAL has funding for Guilherme and Soon Yung to work full time on the project.

Philippe asked about the computing environment. Seth suggested keeping it open
and use spack.

For documentation we will use GitHub, at least for now.

Slides for the CERN Geant4 R&D meeting will be shared soon.



# Fri Mar 27, 2020

Discussed extension of celeritas requirement list:
- List is ample, but it is the needed equivalent information for HEP experiments.
- Description is very general, therefore Kevin Pedro may join the meeting next
  week to help clarifying the requirements.

CERN Geant4 R&D meeting:
- Team decided to aim for Apr 14 instead of Mar 31st.
- Focus of the talk so far is to present the team, describe the scope of the
project, and show openness to engage with the community.
- Slides will be sent around for appraisal.


# Fri Apr 3, 2020

Kevin Pedro and Sunanda Banerjee were present. Takeaways of the discussion:

- Current main bottleneck on CMS is disk I/O.
- Habilty to produce full track information is necessary for full adoption in
the long run.
- Keeping hits of sensitive volumes is enough for many cases.
- SIM+DIGI can be done using in-memory information.

**Meeting time changed to every Wednesday, 2 pm, Eastern Time.**
- Kevin and Sunanda are more than welcome to join regularly, but may be present
once every 2 weeks.


# Wed Apr 8, 2020

- Discussion about Geant4 gdml input, and possible routes to parse the data,
since VecGeom does not handles the materials and specified energy cuts.
- CERN Geant4 R&D meeting:
  - 2 talks will be presented:
    - Monte Carlo neutron transport in the ECP Coupled Monte Carlo Neutronics
    and Fluid Flow Simulation of Small Modular Reactor (ExaSMR) project
    - Celeritas: An accelerated charged-particle detector simulation application
    for LHC experiments
  - Slides for the first talk are already on Slack (# general) for appraisal.
  - Slides for the second talk will be available soon.


# Wed Apr 15, 2020

- Guilherme is trying to compile `vecGeom-test` and is running into an error
where headers are searched as `"root/TRootHeader.h"` instead of simply `TRootHeader`.
- Seth is having a null pointer issue when using the CUDA NavigationPool.
- Discussion about the implications of having all the physics code connected to
the transport loop. The larger the code, the more is the usage of on device
registry, which decreases occupancy.
- Recap on Tom's presentations in the Geant4 Working Group meeting on Apr 14 for
the ones who could not make it. The highlights are:
  - Overall good reception.
  - Community is aware of the challenges and agrees that tackling only part of
  the physics is valuable.
  - Being able to simulate EM showers in the calorimeter is a good milestone.
