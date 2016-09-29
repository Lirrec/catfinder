#pragma once

#include <vector>
#include <string>

const std::vector<std::string> sensorNames = {
	"HeadPitch",
	"Head",
	"RWristYaw",
	"RShoulderRoll",
	"Battery",
	"LAnkleRoll",
	"RHipPitch",
	"RAnklePitch",
	"LHipPitch",
	"RKneePitch",
	"LHipYawPitch",
	"LHipRoll",
	"RHipRoll",
	"RShoulderPitch",
	"LHand",
	"LAnklePitch",
	"RElbowRoll",
	"RElbowYaw",
	"RHand",
	"RHipYawPitch",
	"LWristYaw",
	"LElbowRoll",
	"LShoulderPitch",
	"LElbowYaw",
	"HeadYaw",
	"LKneePitch",
	"LShoulderRoll",
	"RAnkleRoll"
};

const std::vector<std::string> relevantEventNames = {
	"ALAnimatedSpeech / EndOfAnimatedSpeech",
	"ALMemory/KeyAdded",
	"ALMemory/KeyRemoved",
	"ALMemory/KeyTypeChanged",
	"ALMotion/MoveFailed",
	"ALMotion/Protection/DisabledDevicesChanged",
	"ALMotion/Safety/ChainVelocityClipped",
	"ALMotion/Safety/MoveFailed",
	"ALMotion/Safety/PushRecovery",
	"ALMotion/Safety/RobotPushed",
	"ALMotion/Stiffness/restFinished",
	"ALMotion/Stiffness/restStarted",
	"ALMotion/Stiffness/wakeUpFinished",
	"ALMotion/Stiffness/wakeUpStarted",
	"ALTextToSpeech/CurrentBookMark",
	"ALTextToSpeech/CurrentSentence",
	"ALTextToSpeech/CurrentWord",
	"ALTextToSpeech/PositionOfCurrentWord",
	"ALTextToSpeech/Status",
	"ALTextToSpeech/TextDone",
	"ALTextToSpeech/TextInterrupted",
	"ALTextToSpeech/TextStarted",
	"BatteryChargeCellVoltageMinChanged",
	"BatteryChargeChanged",
	"BatteryChargingFlagChanged",
	"BatteryDisChargingFlagChanged",
	"BatteryEmpty",
	"BatteryFullChargedFlagChanged",
	"BatteryLowDetected",
	"BatteryNearlyEmpty",
	"BatteryNotDetected",
	"BatteryPowerPluggedChanged",
	"ChestButtonPressed",
	"DeviceNoLongerHotDetected",
	"FrontTactilTouched",
	"HandLeftBackTouched",
	"HandLeftLeftTouched",
	"HandLeftRightTouched",
	"HandRightBackTouched",
	"HandRightLeftTouched",
	"HandRightRightTouched",
	"HeadProcessorIsCriticallyHot",
	"HeadProcessorIsHot",
	"HotDeviceDetected",
	"HotJointDetected",
	"LeftBumperPressed",
	"MiddleTactilTouched",
	"PostureChanged",
	"RearTacticleTouched",
	"RightBumperPressed",
	"robotHasFallen",
	"robotIsFalling",
	"robotIsWakeUp",
	"robotPoseChanged",
	"SonarLeftDetected",
	"SonarLeftNothingDetected",
	"SonarRightDetected",
	"SonarRightNothingDetected",
	"TemperatureDiagnosisErrorChanged",
	"TemperatureStatusChanged",
	"TouchChanged"
};

const int EVENT_QUEUE_SIZE = 100;