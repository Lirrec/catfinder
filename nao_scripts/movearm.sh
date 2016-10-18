 #!/bin/bash
 qicli call ALRobotPosture.goToPosture "StandInit" 0.1
 qicli call ALMotion.wbEnable 1
 qicli call ALMotion.wbEnableEffectorControl "RArm" 1
 for i in $(seq 1 10)
 do
	qicli call --json ALMotion.wbSetEffectorControl '"RArm"' "[$1, $2, $3]"
	sleep 1
 done
 qicli call ALMotion.wbEnableEffectorControl "RArm" 0
 qicli call ALMotion.wbEnable 0