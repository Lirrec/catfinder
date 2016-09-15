// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"

#include <qi/session.hpp>

#include "NAOSession.h"

UNAOSession::UNAOSession() {
	
}

ENAOIState UNAOSession::getState() {
	return State;
}

template <class... Ts>
void callServiceVoidAsync(std::shared_ptr<qi::Session>& session, std::list<qi::Future<void>>& AsyncCalls, const std::string& serviceName, const std::string& operation, Ts&&... args)
{
	try {
		qi::AnyObject tts = session->service(serviceName);
		qi::Future<void> f = tts.async<void>(operation, args...);
		AsyncCalls.push_back(f);
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}

void UNAOSession::connect(FString naoIP) {
	session.reset(new qi::Session);
	State = ENAOIState::connecting;
	connectionFuture = session->connect(TCHAR_TO_UTF8(*naoIP));

	/*future.wait();
	if (future.hasError()) {
		UE_LOG(LogTemp, Warning, TEXT("Future error %s"), ANSI_TO_TCHAR(future.error().c_str()));
		State = ENAOIState::disconnected;
		return;
	}*/

	UE_LOG(LogTemp, Warning, TEXT("NaoSession connecting to %s"), *naoIP);
	State = ENAOIState::connecting;
}

void UNAOSession::disconnect() {
	UE_LOG(LogTemp, Warning, TEXT("NaoSession disconnecting from %s"), ANSI_TO_TCHAR(session->url().str().c_str()));
	session->close();
	State = ENAOIState::disconnected;
}

bool UNAOSession::isConnected() {
	if (session && State == ENAOIState::connecting) {
		if (connectionFuture.isFinished()) {
			if (connectionFuture.hasError()) {
				UE_LOG(LogTemp, Error, TEXT("NaoSession failed to connect: '%s'"), ANSI_TO_TCHAR(connectionFuture.error().c_str()));
				return false;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("NaoSession successfully connected: '%s'"), ANSI_TO_TCHAR(session->url().str().c_str()));
				State = ENAOIState::connected;
				updateAsyncResults();
				return true;
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("Nao Session still connecting"));
		return false;
	}

	if (!session || !session->isConnected() ) {
		UE_LOG(LogTemp, Warning, TEXT("Nao Session not connected"));
		State = ENAOIState::disconnected;
		return false;
	}


	updateAsyncResults();
	return true;
}

void UNAOSession::updateAsyncResults() {
	for (auto& f : AsyncCalls) {
		if (f.isFinished()) {
			if (f.hasError()) {
				UE_LOG(LogTemp, Error, TEXT("Error on async nao calls: '%s'"), ANSI_TO_TCHAR(f.error().c_str()));
				return;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Successful async call."));
				return;
			}
		}
	}
}

UNaoData* UNAOSession::getData() {
	if (Data.Num() == 0) Data.Push(NewObject<UNaoData>());
	return Data.Top();
}

void UNAOSession::text2SpeechSay(FString message) {
	if (!isConnected()) return;
	callServiceVoidAsync(session, AsyncCalls, "ALTextToSpeech", "say", TCHAR_TO_UTF8(*message));
}

int UNAOSession::getTemperature(FString deviceName) {
	return getALMemoryInt(TEXT("Device/SubDeviceList/") + deviceName + TEXT("/Temperature/Sensor/Value"));
}

void UNAOSession::angleInterpolation(FString targetJoint, float degrees, float time, bool isAbsolute) {
	if (!isConnected()) return;
	callServiceVoidAsync(session, AsyncCalls, "ALMotion", "angleInterpolation", TCHAR_TO_UTF8(*targetJoint), degrees, time, isAbsolute);
}

void UNAOSession::moveTo(float xDistanceInMeters, float yDistanceInMeters, float thetaInRadians) {
	if (!isConnected()) return;
	callServiceVoidAsync(session, AsyncCalls, "ALMotion", "moveTo", xDistanceInMeters, yDistanceInMeters, thetaInRadians);
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
	if (isConnected()) return -1;

	try {
		qi::AnyObject tts = session->service("ALasdfMemory");

		return tts.call<int>("getData", TCHAR_TO_UTF8(*key));
	}
	catch (const std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("std Exception: %s"), ANSI_TO_TCHAR(e.what()));
		return -1;
	}
}
