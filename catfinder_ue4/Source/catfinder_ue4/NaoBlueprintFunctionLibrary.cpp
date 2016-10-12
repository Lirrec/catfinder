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
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().text2SpeechSay(message);
}

void UNAOBlueprintFunctionLibrary::angleInterpolation(UNAOSession* session, FString targetJoint, float rad, float time, bool isAbsolute) {
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().angleInterpolation(targetJoint, rad, time, isAbsolute);
}

void UNAOBlueprintFunctionLibrary::angleInterpolationWithSpeed(UNAOSession* session, FString targetJoint, float rad, float speed) {
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().angleInterpolationWithSpeed(targetJoint, rad, speed);
}

int UNAOBlueprintFunctionLibrary::getTemperature(UNAOSession* session, FString deviceName) {
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	return session->getAPI().getTemperature(deviceName);
}

void UNAOBlueprintFunctionLibrary::moveTo(UNAOSession* session, float xDistanceInMeters, float yDistanceInMeters, float thetaInRadians) {
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().moveToward(xDistanceInMeters, yDistanceInMeters, thetaInRadians);
}

void UNAOBlueprintFunctionLibrary::moveToward(UNAOSession* session, float xSpeedRelative, float ySpeedRelative, float thetaSpeedRelative) {
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().moveToward(xSpeedRelative, ySpeedRelative, thetaSpeedRelative);
}

void UNAOBlueprintFunctionLibrary::stopMove(UNAOSession* session) {
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().stopMove();
}

int UNAOBlueprintFunctionLibrary::getALMemoryInt(UNAOSession* session, FString key) {
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	return session->getAPI().getALMemoryInt(key);
}


void  UNAOBlueprintFunctionLibrary::setALMemoryString(UNAOSession* session, FString key, FString value) {
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().setALMemoryString(key, value);
}

FString  UNAOBlueprintFunctionLibrary::getALMemoryString(UNAOSession* session, FString key) {
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	return session->getAPI().getALMemoryString(key);
}


void UNAOBlueprintFunctionLibrary::startStream(UNAOSession* session, FString myIP) {
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().setALMemoryString("catfinder_ip", myIP);
	session->getAPI().launchProgram("/home/nao/nao_scripts/starth264stream.sh");
}

void UNAOBlueprintFunctionLibrary::stopStream(UNAOSession* session) {
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().launchProgram("/home/nao/nao_scripts/stopstream.sh");
}

void UNAOBlueprintFunctionLibrary::moveHeadToZeroPosition(UNAOSession* session) {
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	std::vector<std::string> strings = { "HeadYaw","HeadPitch" };
	session->getAPI().angleInterpolation(qi::AnyValue::from(strings), qi::AnyValue::from(0.52), qi::AnyValue::from(1.0), true);
}

void UNAOBlueprintFunctionLibrary::setAutonomousState(UNAOSession* session, ENAOALState state)
{
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().setAutonomousState(state);
}

void UNAOBlueprintFunctionLibrary::goToPosture(UNAOSession* session, FString name)
{
	verifyf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().goToPosture(name);
}
