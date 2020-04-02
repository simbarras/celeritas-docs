Stepping overview
=================

For each track, and hence for each particle we repeat the following
steps until the track is marked as stopped or killed.

  1. Select process (AlongStep or PostStep) with shortest ‘proposed
     physics interaction length’ -> [ Process, Type, Length ]

  2. Find next Geometry boundary

  3. MSC preparation

  4. Integrate Equation of Motion

  5. While did-not-reach-physics-length and did-not-cross-boundary

     - Find next Geometry boundary

     - Integrate Equation of Motion

  6. Increase track time, decrease current interaction length. Delayed
     updates from MSC AlongStep.

  7. For each along process

     - if Track not stopped then do AlongStep actions

  8. If Track not stopped and Type == Post then do (single) Process
     PostStep action

  9. If Track stopped then

     - Select AtRest Process [0, 1 or more if some are forced]

     - Do AtRest action for selected processed

  10. Sensitive Hit recording

  11. UserAction(s)

.. note::

   - Along [Step] refers to continuous processes

   - Post [Step] refers to discrete processes.

   - Type is either “Along” or “Post” if the selected process is,
     respectively, continuous or discrete.

   - Secondaries can be produced by the actions (DoIt) of PostStep, AlongStep
     and AtRest processes.

Possible pseudo code implementation (leveraging function pointers)
==================================================================

For each track, and hence for each particle we repeat the following
steps until the track is marked as stopped or killed.

Outer Stepping function:
------------------------

1. Select process (Along or Post) which shortest ‘proposed physics
   interaction length’ and gather: [ Process, Type, Proposed Step Length,
   ProcessFunc to be executed ]

2. Find next Geometry boundary

3. MSC preparation

4. Inner Function (ProcessFunc)

5. Sensitive Hit recording

6. User Action(s)

Note: Having an inner function is not strictly necessary but allow to
express the “early termination” of that code path via return statements.


InnerFunc(ProcessFunc):
-----------------------

a. Integrate Equation of Motion

b. ::
     if !alive **return**

c. while did not reach physics length and did not cross a geometrical
   boundary::

     Find next Geometry boundary
     Integrate Equation of Motion
     if !alive **return**

d. Increase time, decrease interaction length. Delayed updates from MSC
   AlongStep.

e. exec ProcessFunc

ProcessFunc one of:
~~~~~~~~~~~~~~~~~~~

A. Continuous process (AlongStep) was selected (proposed the shortest
   interaction length) ; also includes the “always-on” continuous
   processes.::

     For each AlongStep process
       AlongStepDoIt
       if stopped
         if alive and has-at-rest-processes
           exec AtRest
         **return**

B. Discrete process (PostStep) was selected ; also includes the
   “always-on” continuous and discrete processes.::

     For each along process
       AlongStepDoIt
       if stopped
         if alive && has-at-rest-processes
          exec AtRest
         **return**

     For selected PostStep
       PostStepDoIt
         if stopped
           if alive && has-at-rest-processes
             exec AtRest
           **return**

or

.. _processfunc-one-of-1:

ProcessFunc one of:
~~~~~~~~~~~~~~~~~~~

A. Continuous process (AlongStep) was selected, has-at-rest-processes::

     For each along process
       AlongStepDoIt
       if stopped
         if alive
           exec AtRest
         return

B. Continuous process (AlongStep) was selected, no at rest::

     For each along process
       AlongStepDoIt
       if stopped
         return

C. Discrete process (PostStep) was selected, has-at-rest-processes::

     For each along process
       AlongStepDoIt
       if stopped
         if alive
           exec AtRest
         return

     For selected PostStep
       PostStepDoIt
       if stopped
         if alive
           exec AtRest
         return

D. Discrete process (PostStep) was selected, no at rest::

     For each along process
       AlongStepDoIt
       if stopped
         return

     For selected PostStep
       PostStepDoIt
       if stopped
         return

Jump/Shortcut types:
====================

This is the list of cases where the track processing **can** take a
shortcut:

stopped
  go to AtRest or UserActions (from AlongStep, PostStep)

new
  go to UserActions (from AtRest, PostStep)

killed
  go to UserActions (from AtRest, FastSim, Field (x2), PreStep (UserAction per
  se))

loop
  go to GeometryQuery [looping per se] (from Field)

after-geometry-query
  go to PrePropagation (first time) or to PropagationStage (the other times)

Differences between GeantV and Geant4
=====================================

- It seems that in Geant4 a stopped-but-alive particle will go through the
  UserAction both before and after the AtRest processes while in GV it
  will go through the UserAction after the AtRest.

- In Geant4, “Transportation” (integration of the equation of motion and
  then movement, also called propagation) is both a continuous and
  discrete process always executed “first”

- Actual integration done in AlongStepGetPhysicalInteractionLength but not
  TrackState change, updates are cached in the ‘Transport’ object.

- Updates are applied in AlongStepDoIt

- ‘Relocation’ (and other house cleaning) done in PostStepDoIt

- Geant4 has a vector of processes for Rest, Along and Post for **both**
  the GetProposedInteractionLength and for the DoIt/Action. The two
  corresponding vectors are in **reverse** order …

- So, in the PostStep actions’ vector of processes the Transportation
  process is first while in the GPIL vector it is last …

- Geant4 executes all the steps for a given track in a row before moving
  on to the next track on the queue.

- GeantV after each sub-step (Stages) put the track on a stage specific
  queue. It processes stage by stage with each stage emptying its queue
  before moving on. Jump/Shortcut are implemented by moving the track to
  the appropriate Stage’s queue.

Glossary
========

Geant4 process selection ‘status’
---------------------------------

ExclusivelyForced
  Used by FastSimulation to ask the SteppingManager to
  ignore the other Processes (see G4FastSimulationManagerProcess) [nothing
  seems to prevent 2 ExclusivelyForced processed … (to be cross checked)]

StrongForced
  Run always … even when ExclusivelyForced is used

Forced
  run even if on boundary but not if ExclusivelyForced. (eg MSC)

GeantV stages:
--------------

PreStep
  scheduler sets the track as starting the step

FastSimulation
  shortcut.

ComputeIntLS
  normal (non msc) physics step limit computation.

GeomQueryStage
  Find next boundary

PrePropagation
  call alongStepLimitationLength for MSC (Multiple
  Scattering)

Propagation
  integration of the equation of motion (in a magnetic field
  if particle is not neutral)

PostPropagation
  MSC along step, increase time, decrease interaction
  length.

AlongStep
  continuous processes.

PostStep
  eg. produces the secondaries for an in-flight hadronic process
  (One of the stages that can generate secondaries)

AtRest
  eg. sample the target isotope and produces the secondaries for
  an at-rest hadronic process

SteppingAction
  User actions - done even if the particle is killed.
