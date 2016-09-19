// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"

#include <qi/session.hpp>

#include "NAOData.h"
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
		qi::AnyObject service = session->service(serviceName);
		qi::Future<void> f = service.async<void>(operation, args...);
		AsyncCalls.push_back(f);
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}

void UNAOSession::connect(FString NAOIP) {
	session.reset(new qi::Session);
	State = ENAOIState::connecting;
	connectionFuture = session->connect(TCHAR_TO_UTF8(*NAOIP));

	UE_LOG(LogTemp, Warning, TEXT("NAOSession connecting to %s"), *NAOIP);
	State = ENAOIState::connecting;
}

void UNAOSession::disconnect() {
	UE_LOG(LogTemp, Warning, TEXT("NAOSession disconnecting from %s"), ANSI_TO_TCHAR(session->url().str().c_str()));
	session->close();
	State = ENAOIState::disconnected;
}

bool UNAOSession::isConnected() {
	if (session && State == ENAOIState::connecting) {
		if (connectionFuture.isFinished()) {
			if (connectionFuture.hasError()) {
				UE_LOG(LogTemp, Error, TEXT("NAOSession failed to connect: '%s'"), ANSI_TO_TCHAR(connectionFuture.error().c_str()));
				State = ENAOIState::disconnected;
				return false;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("NAOSession successfully connected: '%s'"), ANSI_TO_TCHAR(session->url().str().c_str()));
				State = ENAOIState::connected;
				updateAsyncResults();
				return true;
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("NAO Session still connecting"));
		return false;
	}

	if (!session || !session->isConnected() ) {
		UE_LOG(LogTemp, Warning, TEXT("NAO Session not connected"));
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
				UE_LOG(LogTemp, Error, TEXT("Error on async NAO calls: '%s'"), ANSI_TO_TCHAR(f.error().c_str()));
				return;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Successful async call."));
				return;
			}
		}
	}
}

UNAOData* UNAOSession::getData() {
	if (Data.Num() == 0) Data.Push(NewObject<UNAOData>());
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
	if (!isConnected()) return;
	callServiceVoidAsync(session, AsyncCalls, "ALMotion", "moveToward", xSpeedRelative, ySpeedRelative, thetaSpeedRelative);
}

void UNAOSession::stopMove() {
	if (!isConnected()) return;
	callServiceVoidAsync(session, AsyncCalls, "ALMotion", "stopMove");
}


int UNAOSession::getALMemoryInt(FString key) {
	if (isConnected()) return -1;

	try {
		qi::AnyObject alm = session->service("ALMemory");

		return alm.call<int>("getData", TCHAR_TO_UTF8(*key));
	}
	catch (const std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("std Exception: %s"), ANSI_TO_TCHAR(e.what()));
		return -1;
	}
}

void UNAOSession::updateData() {
	/*UWorld* const world = GetWorld();
	if (world) {
		if (lastUpdate + updateDelay < world->RealTimeSeconds) {
			
		}
	}*/
	getTemperatures();
}

std::vector<std::string> sensorNames = {
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

void UNAOSession::getTemperatures() {
	if (temperatureResult.isValid()) {

		if (!temperatureResult.isFinished()) return;

		if (temperatureResult.hasError()) {
			UE_LOG(LogTemp, Warning, TEXT("QI Future Error: %s"), ANSI_TO_TCHAR(temperatureResult.error().c_str()));
			return;
		}

		UNAOData* data = getData();
		data.temperatures.Reset();
		

		std::vector<int> temps = temperatureResult.value();

		int idx = 0;
		for (int temp : temps) {
			data.temperatures[ANSI_TO_TCHAR(sensorNames[idx++].c_str())] = temp;
			UE_LOG(LogTemp, Warning, TEXT("Temp: %s %i"), ANSI_TO_TCHAR(sensorNames[idx++].c_str()), temp);
		}
	}
	else {
		std::vector<std::string> temperatureSensorNames;
		temperatureSensorNames.reserve(sensorNames.size());

		for (const auto& joint : sensorNames) {
			temperatureSensorNames.push_back("Device/SubDeviceList/" + joint + "/Temperature/Sensor/Value")
		}

		// no valid future, check if we should start the next call
		// TODO: actually check based on some Timer
		try {
			qi::AnyObject tts = session->service("ALMemory");
			temperatureResult = tts.async<std::vector<int>>("getListData", temperatureSensorNames);
		}
		catch (std::exception& e) {
			UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
		}
	}
}