# Shift/Geant rosetta stone

## Transport

|  Shift                  |   Geant                 |
| ----------------------- |  ---------------------- |
| History                 |  Event                  |
| Source particle         |  Primary particle       |
| Particle                |  Track                  |
| Particle type           |  Particle               |   
| Transport               |  Tracking?              |
| Tracking?               |  Navigation             |
| Tally                   |  Sensitive detector     |
| Cutoffs                 |  Cuts                   |

"Transport" in Shift refers to the entire simulation (after setup and before
teardown). "Transportation" in Geant encompasses the particle's movement within
a geometric region: limiting the tracking distance and updating the particle's
internal clock.

## Geometry

|  Geometria               |  Geant                  | 
| ------------------------ | ----------------------- |
| Move                     | Propagate               |
| Geometry                 | Navigator               |
| Shape                    | Solid                   |
| Cell                     | Physical Volume         |
| [Unique cell]            | Touchable history (?)   |
| kd-tree acceleration     | Voxelization            |


|  VecGeom                 |  Geant                  | 
| ------------------------ | ----------------------- |
| Unplaced volume          | Logical Volume          |
| Placed volume            | Physical Volume         |


## Physics

|  Shift                   |  Geant               |  
| ------------------------ | -------------------- |
| Collision                | Interaction          |
| Bank                     | TrackVector          |

