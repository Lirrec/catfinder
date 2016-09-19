// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <array>
#include <memory>
#include <list>
#include <qi/future.hpp>
#include "NAOData.h"
#include "NAOSession.generated.h"


namespace qi {
	class Session;
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

	UFUNCTION(BluePrintCallable, Category = "NAOInterface")
	ENAOIState getState();
	
	UFUNCTION(BluePrintCallable, Category = "NAOInterface")
	void connect(FString NAOIP);

	UFUNCTION(BluePrintCallable, Category = "NAOInterface")
	void disconnect();
	
	UFUNCTION(BluePrintCallable, Category = "NAOInterface")
	UNAOData* getData();


	UFUNCTION(BlueprintCallable, Category = "NAO")
		void text2SpeechSay(FString message = TEXT("Test!"));

	UFUNCTION(BlueprintCallable, Category = "NAO")
		void angleInterpolation(FString targetJoint, float degrees, float time, bool isAbsolute = true);

	UFUNCTION(BlueprintCallable, Category = "NAO")
		int getTemperature(FString deviceName);

	//Should look at moveToward, comments say its whats supposed to be used w/ joysticks etc.
	UFUNCTION(BlueprintCallable, Category = "NAO")
		void moveTo(float xDistanceInMeters, float yDistacneInMeters, float thetaInRadians);

	UFUNCTION(BlueprintCallable, Category = "NAO")
		void moveToward(float xSpeedRelative, float ySpeedRelative, float thetaSpeedRelative);

	UFUNCTION(BlueprintCallable, Category = "NAO")
		void stopMove();

	UFUNCTION(BlueprintCallable, Category = "NAO")
		int getALMemoryInt(FString key);

	UFUNCTION(BlueprintCallable, Category = "NAO")
		void updateData();

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
	qi::Future<std::vector<int>> temperatureResult;
};
