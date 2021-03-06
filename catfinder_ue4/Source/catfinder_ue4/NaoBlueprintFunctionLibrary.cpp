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

bool UNAOBlueprintFunctionLibrary::isConnected(UNAOSession* session)
{
	UE_LOG(LogTemp, Warning, TEXT("NAO: resetting Sessions."));
	return session->isConnected();
}

void UNAOBlueprintFunctionLibrary::text2SpeechSay(UNAOSession* session, FString message) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().text2SpeechSay(message);
}

void UNAOBlueprintFunctionLibrary::angleInterpolation(UNAOSession* session, FString targetJoint, float rad, float time, bool isAbsolute) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().angleInterpolation(targetJoint, rad, time, isAbsolute);
}

void UNAOBlueprintFunctionLibrary::angleInterpolationWithSpeed(UNAOSession* session, FString targetJoint, float rad, float speed) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().angleInterpolationWithSpeed(targetJoint, rad, speed);
}

int UNAOBlueprintFunctionLibrary::getTemperature(UNAOSession* session, FString deviceName) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	return session->getAPI().getTemperature(deviceName);
}

void UNAOBlueprintFunctionLibrary::moveTo(UNAOSession* session, float xDistanceInMeters, float yDistanceInMeters, float thetaInRadians) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().moveToward(xDistanceInMeters, yDistanceInMeters, thetaInRadians);
}

void UNAOBlueprintFunctionLibrary::moveToward(UNAOSession* session, float xSpeedRelative, float ySpeedRelative, float thetaSpeedRelative) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().moveToward(xSpeedRelative, ySpeedRelative, thetaSpeedRelative);
}

void UNAOBlueprintFunctionLibrary::stopMove(UNAOSession* session) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().stopMove();
}

int UNAOBlueprintFunctionLibrary::getALMemoryInt(UNAOSession* session, FString key) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	return session->getAPI().getALMemoryInt(key);
}


void  UNAOBlueprintFunctionLibrary::setALMemoryString(UNAOSession* session, FString key, FString value) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().setALMemoryString(key, value);
}

FString  UNAOBlueprintFunctionLibrary::getALMemoryString(UNAOSession* session, FString key) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	return session->getAPI().getALMemoryString(key);
}


void UNAOBlueprintFunctionLibrary::startStream(UNAOSession* session, FString myIP) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().setALMemoryString("catfinder_ip", myIP);
	session->getAPI().launchProgram("/home/nao/nao_scripts/starth264stream.sh");
}

void UNAOBlueprintFunctionLibrary::stopStream(UNAOSession* session) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().launchProgram("/home/nao/nao_scripts/stopstream.sh");
}

void UNAOBlueprintFunctionLibrary::moveHeadToZeroPosition(UNAOSession* session) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	std::vector<std::string> strings = { "HeadYaw","HeadPitch" };
	session->getAPI().angleInterpolation(qi::AnyValue::from(strings), qi::AnyValue::from(0.52), qi::AnyValue::from(1.0), true);
}

void UNAOBlueprintFunctionLibrary::setAutonomousState(UNAOSession* session, ENAOALState state)
{
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().setAutonomousState(state);
}

void UNAOBlueprintFunctionLibrary::goToPosture(UNAOSession* session, FString name)
{
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().goToPosture(name);
}

void UNAOBlueprintFunctionLibrary::registerInitialEvents(UNAOSession* session)
{
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getEventManager().registerInitialEvents();
}

FString UNAOBlueprintFunctionLibrary::getOneEvent(UNAOSession* session)
{
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	return session->getEventManager().popEvent();
}

FString UNAOBlueprintFunctionLibrary::dateToString(FDateTime time)
{
	return time.GetTimeOfDay().ToString();
}


void UNAOBlueprintFunctionLibrary::setWholeBodyEnabled(UNAOSession* session, bool state) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().setWholeBodyEnabled(state);
}


void UNAOBlueprintFunctionLibrary::setEnableEffectorControl(UNAOSession* session, FString effectorName, bool state) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().setEnableEffectorControl(effectorName, state);
}


void UNAOBlueprintFunctionLibrary::setEffectorControl(UNAOSession* session, FString effectorName, FVector position) {
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().setEffectorControl(effectorName, position );
}

void UNAOBlueprintFunctionLibrary::setPositions(UNAOSession* session, FString effectorName, ENAOFRAMES frame, FVector position, FVector orientation, float fractionMaxSpeed)
{
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().setPositions(std::vector<std::string>{ TCHAR_TO_UTF8(*effectorName) }, frame, position, orientation, fractionMaxSpeed);
}

void UNAOBlueprintFunctionLibrary::rest(UNAOSession* session)
{
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().rest();
}

void UNAOBlueprintFunctionLibrary::playWebAudioStream(UNAOSession* session, FString url, float volume, float balance)
{
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().playWebAudioStream(url, volume, balance);
}

void UNAOBlueprintFunctionLibrary::stopAllAudioSources(UNAOSession* session)
{
	checkf(session != nullptr, TEXT("UNAOBlueprintLibrary: Expected NAOSession, got nullptr!"));
	session->getAPI().stopAllAudioSources();
}
