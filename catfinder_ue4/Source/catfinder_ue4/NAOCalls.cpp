// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NAOCalls.h"

template <class... Ts>
void postService(std::shared_ptr<qi::Session> session, const std::string& serviceName, const std::string& operation, Ts&&... args)
{
	try {
		if (!session->isConnected()) {
			UE_LOG(LogTemp, Warning, TEXT("postService: Session is not connected!"));
			return;
		}
		qi::AnyObject service = session->service(serviceName);
		service.post(operation, std::forward<Ts>(args)...);
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("postService: Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}

template <class R, class... Ts>
R callService(std::shared_ptr<qi::Session> session, const std::string& serviceName, const std::string& operation, Ts&&... args)
{
	try {
		if (!session->isConnected()) {
			UE_LOG(LogTemp, Warning, TEXT("callService: Session is not connected!"));
			return {};
		}
		qi::AnyObject service = session->service(serviceName);
		return service.call<R>(operation, std::forward<Ts>(args)...);
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("callService: Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}

	return{};
}



int NAOCalls::getTemperature(FString deviceName) {
	return getALMemoryInt(TEXT("Device/SubDeviceList/") + deviceName + TEXT("/Temperature/Sensor/Value"));
}

void NAOCalls::angleInterpolation(FString targetJoint, float degrees, float time, bool isAbsolute) {
	if (!session->isConnected()) return;
	postService(session, "ALMotion", "angleInterpolation", TCHAR_TO_UTF8(*targetJoint), degrees, time, isAbsolute);
}

void NAOCalls::angleInterpolation(qi::AnyValue targetJoint, qi::AnyValue degrees, qi::AnyValue time, bool isAbsolute) {
	if (!session->isConnected()) return;
	postService(session, "ALMotion", "angleInterpolation", targetJoint, degrees, time, isAbsolute);
}


void NAOCalls::moveTo(float xDistanceInMeters, float yDistanceInMeters, float thetaInRadians) {
	postService(session, "ALMotion", "moveTo", xDistanceInMeters, yDistanceInMeters, thetaInRadians);
}


void NAOCalls::moveToward(float xSpeedRelative, float ySpeedRelative, float thetaSpeedRelative) {
	postService(session, "ALMotion", "moveToward", xSpeedRelative, ySpeedRelative, thetaSpeedRelative);
}

void NAOCalls::stopMove() {
	postService(session, "ALMotion", "stopMove");
}

void NAOCalls::text2SpeechSay(FString message) {
	postService(session, "ALTextToSpeech", "say", TCHAR_TO_UTF8(*message));
}


int NAOCalls::getALMemoryInt(FString key) {
	if (session->isConnected()) return -1;
	return callService<int>(session, "ALMemory", "getData", TCHAR_TO_UTF8(*key));
}


void NAOCalls::setALMemoryString(FString key, FString value) {
	postService(session, "ALMemory", "insertData", TCHAR_TO_UTF8(*key), TCHAR_TO_UTF8(*value));
}

FString NAOCalls::getALMemoryString(FString key) {
	if (session->isConnected()) return FString();
	std::string re = callService<std::string>(session, "ALMemory", "getData", TCHAR_TO_UTF8(*key));
	return FString(re.c_str());
}

void NAOCalls::launchProgram(FString name) {
	postService(session, "ALLauncher", "launchExecutable", TCHAR_TO_UTF8(*name));
}

void NAOCalls::goToPosture(FString name)
{
	postService(session, "ALRobotPosture", "goToPosture", TCHAR_TO_UTF8(*name), 1);
}

void NAOCalls::setAutonomousState(ENAOALState newState)
{
	switch ( newState )
	{
	case ENAOALState::solitary:
		postService(session, "ALAutonomousLife", "setState", "solitary");
		break;
	case ENAOALState::interactive:
		postService(session, "ALAutonomousLife", "setState", "interactive");
		break;
	case ENAOALState::disabled:
		postService(session, "ALAutonomousLife", "setState", "disabled");
		break;
	default: break;
	}
}
