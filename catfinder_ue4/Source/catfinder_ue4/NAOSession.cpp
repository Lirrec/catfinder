// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"

#include <algorithm>
#include <qi/session.hpp>


#include "NAOData.h"
#include "NAOSession.h"

UNAOSession::UNAOSession() {
	AsyncCalls.clear();
}

ENAOIState UNAOSession::getState() {
	return State;
}

template <class... Ts>
void callServiceVoidAsync(std::shared_ptr<qi::Session>& session, std::list<qi::Future<void>>& AsyncCalls, const std::string& serviceName, const std::string& operation, Ts&&... args)
{
	try {
		qi::AnyObject service = session->service(serviceName);
		
		//service.call<void>(operation, args...);
		qi::Future<void> f = service.async<void>(operation, args...);
		AsyncCalls.push_back(f);
		
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("callService: Exception: %s"), ANSI_TO_TCHAR(e.what()));

	}
	catch (...) {
		UE_LOG(LogTemp, Warning, TEXT("callService: some other Exception. "));
	}
}



void UNAOSession::connect(FString NAOIP) {

	try {
		session = std::make_shared<qi::Session>();
		State = ENAOIState::connecting;
		connectionFuture = session->connect(TCHAR_TO_UTF8(*NAOIP));


		UE_LOG(LogTemp, Warning, TEXT("NAOSession connecting to %s"), *NAOIP);
		State = ENAOIState::connecting;
		NaoIP = NAOIP;
	}
	catch (const std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("Exception while connecting: %s"), ANSI_TO_TCHAR(e.what()));
		State = ENAOIState::disconnected;
		return;
	}
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
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Successful async call."));
			}
		}
	}

	AsyncCalls.erase(std::remove_if(AsyncCalls.begin(), AsyncCalls.end(), [](const auto& elem) {
		return elem.isFinished();
	}), AsyncCalls.end());
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
	if (!isConnected()) return;
	getTemperatures();
}

void UNAOSession::getTemperatures() {
	if (temperatureResult.isValid()) {

		if (!temperatureResult.isFinished()) return;

		if (temperatureResult.hasError()) {
			UE_LOG(LogTemp, Warning, TEXT("QI Future Error: %s"), ANSI_TO_TCHAR(temperatureResult.error().c_str()));
			return;
		}

		UNAOData* data = getData();
		
		if (!data) return;
		data->TemperatureList.Reset();
		

		std::vector<int> temps = temperatureResult.value();

		int idx = 0;
		for (int temp : temps) {
			
			UTemperatureReading* reading = NewObject<UTemperatureReading>();
			reading->Joint = ANSI_TO_TCHAR(sensorNames[idx++].c_str());
			reading->Temperature = temp;
			data->TemperatureList.Add(reading);
			data->sortData();
			//UE_LOG(LogTemp, Warning, TEXT("Temp: %s %i"), ANSI_TO_TCHAR(sensorNames[idx++].c_str()), temp);
		}

		if (idx > 0)
			UE_LOG(LogTemp, Warning, TEXT("Received new %i temperatures"), idx);

		temperatureResult = qi::Future<std::vector<int>>(); 
	}
	else {
		if (!isConnected()) return;
		std::vector<std::string> temperatureSensorNames;
		temperatureSensorNames.reserve(sensorNames.size());

		for (const auto& joint : sensorNames) {
			temperatureSensorNames.push_back("Device/SubDeviceList/" + joint + "/Temperature/Sensor/Value");
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

//Creates a callback for a specified event that will add an entry to a member-List containing the name of the event.
//For a full list of possible events, see http://doc.aldebaran.com/2-1/naoqi-eventindex.html
void UNAOSession::createCallback(FString eventName) {
	try {
		qi::AnyObject alm = session->service("ALMemory");
		qi::AnyObject subscriber = alm.call<qi::AnyObject>("subscriber", TCHAR_TO_ANSI(*eventName));
		//Create a SignalSubscriber that will handle callbacks From NAO
		qi::SignalSubscriber sigSub(qi::AnyFunction::fromDynamicFunction(boost::bind(&UNAOSession::eventCallback, this, eventName, _1)));
		//The signal created by the subscribe function will Always be called 'signal'
		qi::Future<qi::SignalLink> futureLink = subscriber.connect("signal", sigSub);

		futureLink.wait();
		if (futureLink.hasError()) {
			UE_LOG(LogTemp, Error, TEXT("Error on Signal connect: '%s'"), ANSI_TO_TCHAR(futureLink.error().c_str()));
		}
		//If the subscriber object isn't stored, the callback will no longer happen
		subscriberList.push_back(subscriber);
		UE_LOG(LogTemp, Warning, TEXT("Signal for Event '%s' connected"), *eventName);
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}

//simple callback, writing message to UE-Logs and adding the event to a membered list when called
qi::AnyReference UNAOSession::eventCallback(FString eventName, const std::vector<qi::AnyReference>& params) {
	UE_LOG(LogTemp, Warning, TEXT("NAOEvent: '%s'"),*eventName);
	eventMap.insert(std::make_pair(std::string(TCHAR_TO_UTF8(*eventName)), params));
	//returntype needs to be anyreference. this solution was taken form official libqi examples
	return qi::AnyReference();
}