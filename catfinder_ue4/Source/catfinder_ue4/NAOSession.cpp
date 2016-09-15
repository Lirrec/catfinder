// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"

#include <qi/session.hpp>

#include "NAOSession.h"

UNAOSession::UNAOSession() {
	
}

ENAOIState UNAOSession::getState() {
	return State;
}

void UNAOSession::connect(FString naoIP) {
	session.reset(new qi::Session);
	State = ENAOIState::connecting;
	qi::Future<void> future = session->connect(TCHAR_TO_UTF8(*naoIP));
	future.wait();
	if (future.hasError()) {
		UE_LOG(LogTemp, Warning, TEXT("Future error %s"), ANSI_TO_TCHAR(future.error().c_str()));
		State = ENAOIState::disconnected;
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("NaoSession connected to %s"), *naoIP);
	State = ENAOIState::connected;
}

void UNAOSession::disconnect() {
	UE_LOG(LogTemp, Warning, TEXT("NaoSession disconnecting from %s"), ANSI_TO_TCHAR(session->url().str().c_str()));
	session->close();
	State = ENAOIState::disconnected;
}

UNaoData* UNAOSession::getData() {
	if (Data.Num() == 0) Data.Push(NewObject<UNaoData>());
	return Data.Top();
}


void UNAOSession::text2SpeechSay(FString message) {
	if (!session || !session->isConnected()) {
		UE_LOG(LogTemp, Warning, TEXT("Nao Session not connected"));
		return;
	}

	try {
		qi::AnyObject tts = session->service("ALTextToSpeech");
		tts.call<void>("say", TCHAR_TO_UTF8(*message));
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}

int UNAOSession::getTemperature(FString deviceName) {
	return getALMemoryInt(TEXT("Device/SubDeviceList/") + deviceName + TEXT("/Temperature/Sensor/Value"));
}

void UNAOSession::angleInterpolation(FString targetJoint, float degrees, float time, bool isAbsolute) {
	if (!session || !session->isConnected()) {
		UE_LOG(LogTemp, Warning, TEXT("Nao Session not connected"));
		return;
	}

	try {
		qi::AnyObject tts = session->service("ALMotion");
		tts.call<void>("angleInterpolation", TCHAR_TO_UTF8(*targetJoint), degrees, time, isAbsolute);
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}

void UNAOSession::moveTo(float xDistanceInMeters, float yDistanceInMeters, float thetaInRadians) {
	if (!session || !session->isConnected()) {
		UE_LOG(LogTemp, Warning, TEXT("Nao Session not connected"));
		return;
	}

	try {
		qi::AnyObject tts = session->service("ALMotion");
		tts.call<void>("moveTo", xDistanceInMeters, yDistanceInMeters, thetaInRadians);
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}


void UNAOSession::moveToward(float xSpeedRelative, float ySpeedRelative, float thetaSpeedRelative) {
	if (!session || !session->isConnected()) {
		UE_LOG(LogTemp, Warning, TEXT("Nao Session not connected"));
		return;
	}

	try {
		qi::AnyObject tts = session->service("ALMotion");
		tts.call<void>("moveToward", xSpeedRelative, ySpeedRelative, thetaSpeedRelative);
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}

void UNAOSession::stopMove() {
	if (!session || !session->isConnected()) {
		UE_LOG(LogTemp, Warning, TEXT("Nao Session not connected"));
		return;
	}

	try {
		qi::AnyObject tts = session->service("ALMotion");
		tts.call<void>("stopMove");
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}


int UNAOSession::getALMemoryInt(FString key) {
	if (!session || !session->isConnected()) {
		UE_LOG(LogTemp, Warning, TEXT("Nao Session not connected"));
		return -1;
	}

	try {
		qi::AnyObject tts = session->service("ALasdfMemory");

		return tts.call<int>("getData", TCHAR_TO_UTF8(*key));
	}
	catch (const std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("std Exception: %s"), ANSI_TO_TCHAR(e.what()));
		return -1;
	}
}
