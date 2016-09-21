// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <array>
#include <memory>
#include <list>
#include <qi/future.hpp>
#include <qi/signal.hpp>
#include <qi/AnyObject.hpp>
#include <qi/session.hpp>
#include "NAOData.h"
#include "NAOConstants.h"
#include "NAOSession.generated.h"


namespace qi {
	//class Session;
}

UENUM(BlueprintType)
enum class ENAOIState : uint8 {
	disconnected UMETA(DisplayName = "Not connected"),
	connecting UMETA(DisplayName = "Currently connecting"),
	connected UMETA(DisplayName = "Connected")
};

UCLASS()
class CATFINDER_UE4_API UNAOSession : public UObject
{
	GENERATED_BODY()

public:
	UNAOSession();

	UFUNCTION(BluePrintCallable, Category = UE_NAO_INTERFACE_CATEGORY)
	ENAOIState getState();
	
	UFUNCTION(BluePrintCallable, Category = UE_NAO_INTERFACE_CATEGORY)
	void connect(FString NAOIP);

	UFUNCTION(BluePrintCallable, Category = UE_NAO_INTERFACE_CATEGORY)
	void disconnect();
	
	UFUNCTION(BluePrintCallable, Category = UE_NAO_INTERFACE_CATEGORY)
	UNAOData* getData();


	UFUNCTION(BlueprintCallable, Category = UE_NAO_CATEGORY)
		void text2SpeechSay(FString message = TEXT("Test!"));

	UFUNCTION(BlueprintCallable, Category = UE_NAO_CATEGORY)
		void angleInterpolation(FString targetJoint, float degrees, float time, bool isAbsolute = true);

	UFUNCTION(BlueprintCallable, Category = UE_NAO_CATEGORY)
		int getTemperature(FString deviceName);

	//Should look at moveToward, comments say its whats supposed to be used w/ joysticks etc.
	UFUNCTION(BlueprintCallable, Category = UE_NAO_CATEGORY)
		void moveTo(float xDistanceInMeters, float yDistacneInMeters, float thetaInRadians);

	UFUNCTION(BlueprintCallable, Category = UE_NAO_CATEGORY)
		void moveToward(float xSpeedRelative, float ySpeedRelative, float thetaSpeedRelative);

	UFUNCTION(BlueprintCallable, Category = UE_NAO_CATEGORY)
		void stopMove();

	UFUNCTION(BlueprintCallable, Category = UE_NAO_CATEGORY)
		int getALMemoryInt(FString key);

	UFUNCTION(BlueprintCallable, Category = UE_NAO_CATEGORY)
		void updateData();

	//creates a callback for testing purposes, triggers when the naos chestbutton is pressed
	UFUNCTION(BlueprintCallable, Category = UE_NAO_CATEGORY)
		void createCallbackTest(FString eventName);

private:

	bool isConnected();
	void updateAsyncResults();

	ENAOIState State = ENAOIState::disconnected;

	UPROPERTY()
	TArray<UNAOData*> Data;
	
	FString NAOIp;
	std::shared_ptr<qi::Session> session;

	std::list<qi::Future<void>> AsyncCalls;
	qi::Future<void> connectionFuture;

	float lastUpdate;
	float updateDelay;

	void getTemperatures();
	void getTestEvent();
	//simple callback, writing message to UE-Logs when called
	//void testCallback();
	qi::AnyReference testCallback(const std::vector<qi::AnyReference>& params);
	qi::AnyObject callbackBuffer;
	qi::Future<std::vector<int>> temperatureResult;
	qi::Future<qi::SignalLink> f;
	qi::SignalSubscriber sigSub;

	//qi::AnyObject futLink;
};
