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
	//NAOSessionManager::instance()->getSession(TEXT("192.168.1.13"));
	//NAOSessionManager::instance()->getSession(TEXT("10.215.255.187"));
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