
Celeritas Meeting minutes
=========================


# Fri Mar 20, 2020

- Tom presented current budget situation. FWP is in process and the current
document is on Celeritas' General Slack channel.
- Seth described the two milestones for current FWP:
  - VecGeom GPU verification
  - GPU performance demonstration of EM physics using a gdml geometry

- Seth started a Rosetta Stone for nomenclature between Nuclear and HEP physics
to avoid confusion as we move forward. File is available on GitHub.
- Krzysztof suggested talking to Soon Yung about CMS MC. Stefano will work on it.
- FNAL has funding for Guilherme and Soon Yung to work full time on the project.
- Philippe asked about the computing environment. Seth suggested keeping it open
and use spack.
- For documentation we will use GitHub, at least for now.
- Slides for the CERN Geant4 R&D meeting will be shared soon.


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
where headers are searched as `"root/TRootHeader.h"` instead of simply
`TRootHeader`.
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


# Wed Apr 22, 2020

- Guilherme was able to help Seth fix the null pointer issue from last week.
Details on Slack (#vecgeom).
- Seth is not sure how to use `vgdml::Frontend::Load(gdml_filename)`. P. Canal
will look into that.
- Infrastructure build for the transport loop will start soon.


# Wed Apr 29, 2020

- Seth briefly mentioned about his meeting with Amanda, Stefano, and Tom this
morning, which addressed the first steps of the project. Issues were opened in
<https://github.com/celeritas-project/celeritas>.
- Seth asked about the geantino (a non-interacting particle used to
test the transporting mechanism), and if setting all materials to vacuum should
produce the same results (a similar approach is used in Shift).
  - Guilherme: Yes.
- Discussion regarding continuous energy processes in the case of large steps,
which would cause a considerable discrepancy with the correct cross-section
value at the end of the step.
  - Philippe: There is nothing in the code to prevent that to happen, although
  it is believed that this is not an issue in any currently used model.
- Seth asked if particles have different weights in Geant4.
  - Not by default. Biasing exists, but weighting is set to 1 for every particle
  as a standard. CMS has implemented biasing, but this question will need to be
  followed up by CMS people – which were not present in the meeting.


# Wed May 6, 2020
**Meeting adjourned.**


# Wed May 13, 2020

- FWP was signed by Nichols and Marcel. DOE status is TBD. Tom will look into it.  
- Celeritas Startup branch now has initial infrastructure, compiling with CUDA
and Google test (albeit with no tests yet).  
- Seth, Amanda, and Stefano should start working on infrastructure tasks on
Thursday.
- Philippe: What is the plan to converge?
  - A clearer big picture still needs to be defined. For example, Seth prefers
  to use Thrust, which is not used in GeantX.


# Wed May 20, 2020
**Meeting adjourned.**


# Fri May 29, 2020

- Soon briefly updated the team on the HSF simulation workgroup meeting. More at
<https://indico.cern.ch/event/921244/>.
- Amanda worked on the random number generator and will push the update.
- Stefano is implementing a test physics process and will also push the update
soon. A header with constants and units was also created. The team prefers to
add new information as needed, instead of just include CLHEP data.
- Seth will merge celeritas startup branch into master.
- Long discussion regarding the system of units to be used by the Celeritas
internal code. There is not a fully agreed path forward, but an internally
consistent system of units (CGS), with input/output conversion from/to different
applications is preferred by Seth and Tom. Team will revisit the topic as coding
evolves.
- A Slack Poll will be sent to choose a new Celeritas meeting date. The team
also may start a weekly coding meeting on top of the existing Celeritas meeting.
The coding one will probably gather less people and will focus on coding and
technical discussions.


# Wed Jun 3, 2020

- Seth suggests new meeting schedules. Coding meetings will happen on Mondays
and Thursdays at 1 pm (CT) / 2 pm (ET), with biweekly Celeritas meetings taking
place every other Friday at 1 pm (CT) / 2 pm (ET) for more general discussions.


# Fri Jun 12, 2020

- Discussion focused on physics tables produced by Geant4. Several processes
use tables calculated at the beginning of the simulation instead of performing
on the fly calculation at each simulation step.
- Tables are created every time Geant4 is run and can be dumped to disk as ascii
files. This can be done by using the following options in the Geant4-Sandbox:

```
/run/particle/storePhysicsTable PATH_TO_TARGET_STORE_DIR
/run/particle/setStoredInAscii 1
/run/particle/applyCuts true
/run/particle/dumpCutValues all
```

- Tables are calculated based on the loaded physics list and materials from the
gdml file.
- Celeritas will use such tables, which will be pre-generated by Geant4.
- Track and geometry management needs to get started. Seth will start a new
coding meeting with Guilherme on Tuesdays at 2 pm (ET).


# Fri Jul 17, 2020

- Seth inquired about members' availability:
  - Stefano: Full time.
  - Guilherme: 60%-80%.
  - Krzysztof: Monitoring/consulting.
  - Philippe: 50% on Geant related projects (including Celeritas).
  - Sun Yung: Currently at 40%, but will ramp up to 80%.
  - Paul: Monitoring until next FY.
  - Amanda: 90% to full time.
  - Vincent: To be determined.

- Tom's update on funding:
  - Fermilab has received funding for Guilherme and Sun.
  - ORNL still unclear. We should have an update by the next meeting.

- Seth's update on the current status:
  - Data cpu/gpu infrastructure has been set up.
  - Random number generator is being developed.
  - Nomenclature is still being discussed, but good progress has been made.
  - Base code for dealing with geometry, material information, and physics
  processes is converging.

- Paul: How the memory management will be done for secondaries?
  - Seth: current idea is a stack allocator. Code pre-computes the amount of
  secondaries needed to be allocated for every primary and requests allocation
  from the stack. If there is enough memory, it moves forward, otherwise the
  stack allocator returns a null pointer and the physics process exits. In that
  case, the remaining particles will be moved to a queue so they can be
  transported by the next kernel launch.


# Fri Jul 31, 2020

- Tom's funding update:
  - Expected to receive funding for the next FY before September.

- Project's update:
  - Added new code design to Celeritas wiki, everyone is encouraged to provide
  feedback.
  - Seth wrote a new test harness for the KNInteractor.
  - Guilherme is working on vecgeom's magfield propagator.
  - Stefano is working on code to export Geant4 particle and physics table data
  and import it into Celeritas.
  - Amanda is working on random number generators.

- Upcoming HEP update in September. We plan to present a few micro examples on
how the current code is performing.
- Soon suggests a step-by-step installation process sketched up.


# Fri Aug 14, 2020

- Beginning of Sept. Seth and Tom will provide an update to DOE's HEP office.
  - Plan is to have a small demonstration working that includes a small
  straight line propagator by Sept 1.

- New merge requests to be reviewed, which include
  - Particle interactor: changes the particle state and produce secondaries.
  - Importer for Geant data. This MR focuses only on particles.

- Apart from management and consulting:
  - Amanda has been working on infrastructure to generate events on device.
  - Guilherme is working with the vecgeom propagator.

- Project is moving towards a deterministic way of allocating stack memory for  
new particles, which provides simulation reproducibility.


# Fri Aug 28, 2020

- Tom wants to get the LOI ready and sent by Monday, COB. Has to be roughly 2
pages. Document is in the celeritas-doc repository.
- The Celeritas demo app should be merged soon.
- Team agreed with an in depth project briefing on October 14. Seth will sketch
out the schedule. DOE presentation should happen around that same time.


# Fri Sep 11, 2020
**Meeting adjourned.**


# Fri Sep 25, 2020

- Vincent started working on the Bethe Heitler pair production physics model.
For that, he needs material/element data. So now we are in the process of
adding material and volume information to the geant-exporter app and
GeantImporter class.
- Amanda just created a PR for reading data from HepMC/HEPEVT input files and
create events.
- Guilherme is working on the propagator.
- DOE presentation date is not defined still.


# Fri Oct 9, 2020

- Tom: meeting with DOE is most likely to be scheduled at the end of the month.
More information will be provided closer to the real date.
- Philippe: Nov. 19-24: HEP Software Foundation Workshop. There will be a
session on detector simulation, and we are invited to report on Celeritas.
Link: https://indico.cern.ch/event/941278/
- Tom, Seth, and Stefano will schedule a meeting to discuss details and get a
final comparison between the Celeritas KN demo app (both GPU and CPU) and Geant.


# Fri Oct 23, 2020
**Meeting adjourned**


# Fri Oct 30, 2020

- Material properties are almost fully working. That, with tables will provide
a fully working material / XS lookup in Celeritas.
- Discussed possible scenarios in which processes would be selected for each
particle.
- Currently implemented physics vectors are mostly used by EM physics, not
being used by hadronic models, which have their own data structures.
- As soon as Guilherme finishes the propagator, Seth is going to include it in
the demo app, which currently has its own stepping method.
- Event management (production of secondaries) still ongoing work.
- DOE HEP meeting is scheduled to Nov 19th. Slides will be sent beforehand for
everyone's appraisal, and a preview of the presentation will take place on
Nov. 10th.
- New Celeritas Collocation to take place on Nov. 11th.
- We now have a working Klein-Nishina interactor running on both CPU and GPU,
along with a small Geant4 app that runs the same physics process. A rough
summary of the numbers is given below:
  - `Celeritas CPU vs. GPU`: `~100x` improvement from a single Nvidia V100 GPU
  to a single Haswell CPU.
  - `Celeritas GPU vs. Geant4` on a single Haswell CPU:  `~300x` improvement.
  - This is a good time/opportunity to evaluate current design choices, test
  variations, and how they affect the simulation execution.
  - These testings could lay ground for a prospect paper.
  - Philippe: it's important to be careful about the caveats in this comparison.
  Still to be implemented infrastructure, such as stepping management and
  geometry navigation will pay a toll that cannot be quantified at the moment.
  Managing expectations is important to not present future lower (and more
    realistic) numbers which may be interpreted as a failure to achieve the
  standards created by the original improvement factors.


# Fri Nov 13, 2020

- Brief discussion on the DOE HEP presentation. Team is happy with the result.
- Wednesday's hackathon helped pinpointing information that will need to be
implemented for physics interactors to work properly.
  - Soon finished implementation of `e+ -> gamma + gamma` interactor.
- Guilherme: Current raytracing issue is being caused by the fact that VecGeom
has some CPU classes that are not available on GPU.
- Soon started working on the magnetic field propagator.
- Seth: we should start thinking about a backup/contingency plan in case we
continue having compatibility issues with VecGeom.
- Possible future meetings:
  - **25th International Conference on Computing in High Energy & Nuclear
  Physics**, to be held in May 2021. **Paper submission** will open on
  **1 December 2020** and close on **28 February 2021**.
  Link: http://cern.ch/vchep2021


# Fri Nov 27, 2020
**Thanksgiving**


# Fri Dec 11, 2020

- DOE presentation on Nov. 19th went well with an overall enthusiastic feeling, 
including the fact that the team is also collaborating with the U.K. 
- Geant4 10.7 has a new tasking implementation which should provide coupling 
between Celeritas EM physics while running the rest in Geant4. The Acceleritas 
repo is being developed with this purpose.
- HSF-WLCG presentation was based on the DOE one and also went really well. 
There is an apparent acceptance in developing a new code for GPU particle 
transport as opposed to try and port Geant4.
- GPU-based software have been developed in many HEP fronts, such as triggering 
and production, but detector modeling has mostly been limited to GeantX and 
GeantV.
- Current Geant4 collaboration chair is still not a believer that GPUs can be a
solution for detector simulation, but the overall opposition to the idea seems 
to be diminishing.
- Geant4 is open to accept any proved GPU integration into its release, altough
with no internal planned efforts on this front.
- Philippe: Celeritas effort has been distinctive in the fact that the team is 
large enough, with significant time devoted to the project and a clear set of
objectives in place.

- New FY scheduled times devoted to Celeritas:
  - Seth: 90%
  - Stefano: 100%
  - Amanda: 90%
  - Guilherme: 100%
  - Soon: 50%
  - Philippe: 45%

- Current focus areas:
  - Amanda: Mostly finished implementing the mechanics for events/track states.
  - Stefano: physics and Geant4 data import.
  - Guilherme: Restling with VecGeom's issues with initialization and gdml.
  - Soon: Working in the magnetic field propagation.
  - Everyone has been working with different physics interactors.

- Next intermediate step is to use multi-physics with single element materials.

- Possible future conference abstract/full submission: 
https://indico.cern.ch/event/948465/abstracts/


# Fri Dec 25, 2020
**Happy holidays!**


# Fri Jan 8, 2021

- Next DOE meeting should take place in February. The plan is to present a 
second example app with multiple material support and possibly Acceleritas, 
which uses Celeritas along with the Geant4 tasking manager to offload EM 
physics to GPU. 
- Round table on current tasks:
  - Amanda: Event infrastructure and photoelectric effect.
  - Guilherme: linear propagator and Rayleigh scattering.
  - Stefano: eBremSB tables import and Moller-Bhabha scattering.
  - Tom: Multiple scattering process.
  - Soon: Magnetic field propagation.
  - Vincent: Bethe-Heitler interactor.
- New hackathon scheduled to January 20th.
- vCHEP paper is due on Feb 28 [http://cern.ch/vchep2021].


# Fri Jan 22, 2021

- Round table:
  - Stefano: Working on Moller-Bhabha interactor and importing eBremSB data from
  z and ascii files.
  - Amanda: validating the Livermore interactor against G4 and working with 
  process/model testing harnesses.
  - Guilherme: working with cms rasterizer.
  - Soon: working on and validating the magnetic field propagator.
  - Tom: No clear update yet regarding DOE.
  - Ben: Got started with google docs for the physics data and how we can move 
  forward with that.
  - Philippe: Fix root autoload and provide scripts to view data from the 
  geant-exporter-data.root using both root .C macro and .py script. PR merged.
  - Vincent: Finished with Bethe-Heitler. PR is merged. Will start working with 
  the next interactor.
- Celeritas stepping algorithm is on its way.


# Fri Feb 5, 2021

- Team has been pushing forward in the physics side:
  - Substantial progress on physics models by Amanda, Vincent, and Stefano.
  - Soon is making progress on the magnetic field propagator.
  - Work on integration of stepping loop + physics models.
- Today's merged PR provides a new piece of code, namely the Pie class. This is 
a portable data container that has the same interface on both host/device, 
eliminating the complexity for shuffling pointers around. 
- Geometry: Guilherme is now running CMS rasterizer (almost) succesfully. 
Some views can't still be produced (as if the rasterizer ends up in an infinite 
loop). These issues are being studied.
- vCHEP paper will most likely present a demo with 2 physics processes and plans 
for the overall code architecture.
- Paul mentioned the discrepancies between the Geant4 Moller-Bhabha sampler and 
documentation, agreeing with our current understanding. Work on covering these 
discrepancies will be done while validating the Celeritas implementation. 
Stefano followed the code implementation due to the high likelihood that 
extensive MC validations were performed over the years.


# Fri Feb 19, 2021

- DOE-HEP postponed all budget meetings. Despite no new meeting date, we
should still proceed with a self-imposed deadline, as if there were no changes.  
- vCHEP paper due end of Feb. KN demo app tests showed that smaller kernels 
improve occupancy and decrease performance. Due to no divergence in the current 
demo, the effects of breaking the code down into smaller kernels should become 
more prominent after multi-physics is implemented.  
- Physics: we are making good progress on different model implementations and 
stepping loop. Should be able to have multi-physics running on Summit by June.  
- Philippe solved VecGeom issue regarding reloading the geometry. 
- Printed debug statements from VecGeom are an issue. Seth created a wrapper to 
suppress the output, at least while VecGeom main repository does not remove 
these spurious printouts.


# Fri Mar 5, 2021

- Tom, regarding funding: budget still unclear. DOE is excited with current 
results, but not sure how to fund it. Next meeting at the end of March should
provide a clearer scenario. Starting FY23, SCIDAC may become a funding source. 
- Seth outlines the milestones for the next 3 years:
  - End of next year: 
    - Complete EM physics + integration with experimental.
  framework.
    - Possible portability to other platforms.
  - End of 2022: 
    - Runtime performance analysis.
    - EM physics validated in simple and complex geometries.
    - Celeritas + Geant4 integration.
  - End of 2024:
    - Start implementation of hadronic physics with possibility of a full event 
    run by Celeritas.
    - Use Celeritas as a training data generator for AI/ML simulations.
- Daniel: Iterating with the experiments is fundamental to guarantee that
experiments are willing to absorb Celeritas into their frameworks. These 
iterations might be passed via HSF.
- Soon on 3 years plan: hadron physics might start with neutron physics, since 
neutron + EM physics encompass the vast majority of the computing time.
- Witek will present next week on our behalf at the Geant4 Technical forum
(see https://indico.cern.ch/event/1011728/timetable/#20210311.detailed). Most
likely he will present our project plan for 2020-2021 FY. 


# Fri Mar 19, 2021

- Recent progress: Bremmstrahlung is mostly done. This and Rayleigh scattering
are the last major electron/photon missing bits, aside from multiple scattering.
- Upcoming DOE meeting (March 29): We won't have a multi-physics demo app, but
there was tremendous progress and several components are completed, so we have
strong updates.
- April 12: HSF Working Group Meeting will include Celeritas and AdePT updates.
- Seth: Regargind the milestones for the next couple years: in case there are
any suggestions, please add them to the 
`celeritas-docs/project-plan/milestones-2023` repository.


# Fri Apr 2, 2021

- DOE meeting went well. We should hear back from Doug or Marcel regarding
funding in the next week or so.
- Plan to get multiphysics with single element materials up and running soon.
- Multi single-element materials example problem is available in 
`benchmarks/validation`. The gdml file will be also copied to the celeritas repo
for testing and demo app.
- On VecGeom/Root/Geant4 geometry issues (loading/rendering/unit errors) seen in
the past few months:
  - Seth suggests writting a new library that acts as an intermediate layer 
  between the GDML parser and the final G4VSolid/VUnplaced Volume/TGeoShape 
  objects.
  - Philippe: There's currently an effort to add a navigator in Geant4 that uses
  VecGeom interface. This is an interesting point to present in our 
  Celeritas/AdePT monthly meetings.
  - Soon: Parser has 2 layers: reading and writing parts. We could have one gdml
  reader, with different writers to create Geant/VecGeom/Root objects.
  - Seth: another option would be to use `G4GDML -> G4VSolid -> new library`
  instead, which would translate that to vecgeom/root objects.
  - More on this in future meetings, but there has to be consistency between
  the final objects used by G4, VecGeom, and ROOT.


# Fri Apr 16, 2021
**Meeting adjourned**


# Fri Apr 30, 2021
- Team will move to a new and less formal meeting schedule with 2 meeting slots
a week (Mondays and Thursdays) as placeholders to discuss any topic/issue, with
meetings being confirmed as needed.
- Stepping loop hackathon should take place next Thursday.
- Robust hability to link against VecGeom is a pressing issue, and a surrogate
navigator might be needed. Current errors make it impossible for us to run our
demo app. Philippe could not join us today, so a new strategy will be discussed
in a future team meeting.
- No updates from DOE yet regarding our new funding request.


# Fri Oct 8, 2021

- Reconvened after a long strategy meeting hiatus to discuss a few important
updates on our long term plans.
- In this upcoming year, we should have an answer on a new SciDAC-5 partnership
call.
- ORNL has set up a pre-call preparation session now in Oct 22. 
- Tom expects FOA to happen in November. Usually they are due about 3 months
after, thus we might expect the deadline to be around Feb/Mar. We will set up
another meeting to discuss the proposal write up.
- Big goals for the next FY (also outlined on GitHub):
  - **Y2Q1**: fully validated and operational standalone application, providing
  useful statistics and analysis.
  - **Y2Q2**: work on last bits of EM physics, including multiple scattering,
  multiple elements per material and magnetic field.
  - **Y2Q3**: Explore non-Nvidia hardware (including HIP for Frontier).
  - **Y2Q4**: Components needed for integration with experimental workflows,
  such as CMS. That will include scoring data in sensitive detectors and dealing
  with hit output for digitization. We will need to get in touch with CMS
  members and work closely with them to be able to perform a test run.
