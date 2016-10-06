// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NAOBlueprintFunctionLibrary.h"

#include <qi/session.hpp>
#include <qi/future.hpp>
#include "NAOSessionManager.h"


UNAOSession* UNAOBlueprintFunctionLibrary::getNAOInterface(FString ipAddress) {
	return NAOSessionManager::instance()->getSession(ipAddress);
}

void UNAOBlueprintFunctionLibrary::initializeNAOInterfaces() {
	UE_LOG(LogTemp, Warning, TEXT("NAO: initializing Sessions."));
}

void UNAOBlueprintFunctionLibrary::shutdownNAOInterfaces() {
	UE_LOG(LogTemp, Warning, TEXT("NAO: resetting Sessions."));
	NAOSessionManager::instance()->reset();
}


void UNAOBlueprintFunctionLibrary::text2SpeechSay(UNAOSession* session, FString message) {
	session->getAPI().text2SpeechSay(message);
}

void UNAOBlueprintFunctionLibrary::angleInterpolation(UNAOSession* session, FString targetJoint, float degrees, float time, bool isAbsolute) {
	session->getAPI().angleInterpolation(targetJoint, degrees, time, isAbsolute);
}

int UNAOBlueprintFunctionLibrary::getTemperature(UNAOSession* session, FString deviceName) {
	return session->getAPI().getTemperature(deviceName);
}

void UNAOBlueprintFunctionLibrary::moveTo(UNAOSession* session, float xDistanceInMeters, float yDistanceInMeters, float thetaInRadians) {
	session->getAPI().moveToward(xDistanceInMeters, yDistanceInMeters, thetaInRadians);
}

void UNAOBlueprintFunctionLibrary::moveToward(UNAOSession* session, float xSpeedRelative, float ySpeedRelative, float thetaSpeedRelative) {
	session->getAPI().moveToward(xSpeedRelative, ySpeedRelative, thetaSpeedRelative);
}

void UNAOBlueprintFunctionLibrary::stopMove(UNAOSession* session) {
	session->getAPI().stopMove();
}

int UNAOBlueprintFunctionLibrary::getALMemoryInt(UNAOSession* session, FString key) {
	return session->getAPI().getALMemoryInt(key);
}


void  UNAOBlueprintFunctionLibrary::setALMemoryString(UNAOSession* session, FString key, FString value) {
	session->getAPI().setALMemoryString(key, value);
}

FString  UNAOBlueprintFunctionLibrary::getALMemoryString(UNAOSession* session, FString key) {
	return session->getAPI().getALMemoryString(key);
}


void UNAOBlueprintFunctionLibrary::startStream(UNAOSession* session, FString myIP) {
	session->getAPI().setALMemoryString("catfinder_ip", myIP);
	session->getAPI().launchProgram("/home/nao/nao_scripts/starth264stream.sh");
}

void UNAOBlueprintFunctionLibrary::stopStream(UNAOSession* session) {
	session->getAPI().launchProgram("/home/nao/nao_scripts/stopstream.sh");
}

void UNAOBlueprintFunctionLibrary::moveHeadToZeroPosition(UNAOSession* session) {
	std::vector<std::string> strings = { "HeadYaw","HeadPitch" };
	session->getAPI().angleInterpolation(qi::AnyValue::from(strings), qi::AnyValue::from(0.52), qi::AnyValue::from(1.0), true);
}

void UNAOBlueprintFunctionLibrary::setAutonomousState(UNAOSession* session, ENAOALState state)
{
	session->getAPI().setAutonomousState(state);
}

void UNAOBlueprintFunctionLibrary::goToPosture(UNAOSession* session, FString name)
{
	session->getAPI().goToPosture(name);
}
