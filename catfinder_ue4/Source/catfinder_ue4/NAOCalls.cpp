// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NAOCalls.h"

template <class... Ts>
void NAOCalls::postService(const std::string& serviceName, const std::string& operation, Ts&&... args)
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
R NAOCalls::callService(const std::string& serviceName, const std::string& operation, Ts&&... args)
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

template <class R>
R NAOCalls::getALMemory(FString key) {
	if (session->isConnected())
	{
		UE_LOG(LogTemp, Warning, TEXT("getALMemory: Session is not connected, returning empty value!"));
		return R();
	}
	return callService<R>("ALMemory", "getData", TCHAR_TO_UTF8(*key));
}

template <class T>
void NAOCalls::setALMemory(FString key, T&& value) {
	postService("ALMemory", "insertData", TCHAR_TO_UTF8(*key), value);
}


int NAOCalls::getALMemoryInt(FString key) {
	return getALMemory<int>(key);
}

void NAOCalls::setALMemoryString(FString key, FString value) {
	return setALMemory(key, TCHAR_TO_UTF8(*value));
}

FString NAOCalls::getALMemoryString(FString key) {
	if (session->isConnected()) return FString();
	std::string re = getALMemory<std::string>(key);
	return FString(re.c_str());
}





int NAOCalls::getTemperature(FString deviceName) {
	return getALMemoryInt(TEXT("Device/SubDeviceList/") + deviceName + TEXT("/Temperature/Sensor/Value"));
}

void NAOCalls::angleInterpolation(FString targetJoint, float rad, float time, bool isAbsolute) {
	postService("ALMotion", "angleInterpolation", TCHAR_TO_UTF8(*targetJoint), rad, time, isAbsolute);
}

void NAOCalls::angleInterpolation(qi::AnyValue targetJoint, qi::AnyValue rad, qi::AnyValue time, bool isAbsolute) {
	postService("ALMotion", "angleInterpolation", targetJoint, rad, time, isAbsolute);
}

void NAOCalls::angleInterpolationWithSpeed(FString targetJoint, float rad, float speed) {
	postService("ALMotion", "angleInterpolationWithSpeed", targetJoint, rad);
}


void NAOCalls::moveTo(float xDistanceInMeters, float yDistanceInMeters, float thetaInRadians) {
	if (!session->isConnected()) return;
	postService("ALMotion", "moveTo", xDistanceInMeters, yDistanceInMeters, thetaInRadians);
}


void NAOCalls::moveToward(float xSpeedRelative, float ySpeedRelative, float thetaSpeedRelative) {
	postService("ALMotion", "moveToward", xSpeedRelative, ySpeedRelative, thetaSpeedRelative);
}

void NAOCalls::stopMove() {
	postService("ALMotion", "stopMove");
}

void NAOCalls::text2SpeechSay(FString message) {
	postService("ALTextToSpeech", "say", TCHAR_TO_UTF8(*message));
}


void NAOCalls::launchProgram(FString name) {
	postService("ALLauncher", "launchExecutable", TCHAR_TO_UTF8(*name));
}

void NAOCalls::goToPosture(FString name)
{
	postService("ALRobotPosture","goToPosture", TCHAR_TO_UTF8(*name), 1);
}

FString NAOCalls::getPosture()
{
	std::string re = callService<std::string>("ALRobotPosture", "getPosture");
	return FString(re.c_str());
}

void NAOCalls::subscribeToExtractor(FString serviceName)
{
	postService(TCHAR_TO_UTF8(*serviceName), "subscribe", "catfinder");
}

void NAOCalls::unsubscribeFromExtractor(FString serviceName)
{
	postService(TCHAR_TO_UTF8(*serviceName), "unsubscribe", "catfinder");
}

std::vector<float> NAOCalls::getLeftSonarValues()
{
	return callService<std::vector<float>>("ALMemory", "getListData", sonarLeftValues);
}

std::vector<float> NAOCalls::getRightSonarValues()
{
	return callService<std::vector<float>>("ALMemory", "getListData", sonarRightValues);
}

void NAOCalls::setAutonomousState(ENAOALState newState)
{
	switch ( newState )
	{
	case ENAOALState::solitary:
		postService("ALAutonomousLife", "setState", "solitary");
		break;
	case ENAOALState::interactive:
		postService("ALAutonomousLife", "setState", "interactive");
		break;
	case ENAOALState::disabled:
		postService("ALAutonomousLife", "setState", "disabled");
		break;
	default: break;
	}
}

void NAOCalls::setWholeBodyEnabled(bool state) {
	postService("ALMotion", "wbEnable", state);
}

void NAOCalls::setEnableEffectorControl(FString effectorName, bool state) {
	postService("ALMotion", "wbEnableEffectorControl", TCHAR_TO_UTF8(*effectorName), state);
}

void NAOCalls::setEffectorControl(FString effectorName, FVector Coord) {
	postService("ALMotion", "wbSetEffectorControl", std::vector<float> { Coord.X, Coord.Y, Coord.Z });
}

void NAOCalls::setPositions(std::vector<std::string> effectorNames, ENAOFRAMES frame, FVector position, FVector orientation, float fractionMaxSpeed)
{
	std::vector<float> position6d { position.X, position.Y, position.Z, orientation.X, orientation.Y, orientation.Z };
	int axismask = 63;
	postService("ALMotion", "setPositions", effectorNames, (int)frame, position6d, fractionMaxSpeed, axismask);
}

void NAOCalls::rest()
{
	postService("ALMotion", "rest");
}
