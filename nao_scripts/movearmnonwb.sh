 #!/bin/bash
 qicli call ALRobotPosture.goToPosture "StandInit" 0.4
 qicli call --json ALMotion.setPositions '"RArm"' 0 '[0.128771, -0.0835046, 0.242426, 1.70064, -1.26492, 0.268039 ]' 0.6 63