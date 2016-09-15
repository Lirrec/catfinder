// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <array>
#include <memory>
#include <list>
#include <qi/future.hpp>
#include "NaoData.h"
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

	UFUNCTION(BluePrintCallable, Category = "NaoInterface")
	ENAOIState getState();
	
	UFUNCTION(BluePrintCallable, Category = "NaoInterface")
	void connect(FString naoIP);

	UFUNCTION(BluePrintCallable, Category = "NaoInterface")
	void disconnect();
	
	UFUNCTION(BluePrintCallable, Category = "NaoInterface")
	UNaoData* getData();


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
		int getALMemoryInt(FString key);

private:

	bool isConnected();
	void updateAsyncResults();


	ENAOIState State = ENAOIState::disconnected;

	UPROPERTY()
	TArray<UNaoData*> Data;
	
	FString naoIp;
	std::shared_ptr<qi::Session> session;

	std::list<qi::Future<void>> AsyncCalls;
	qi::Future<void> connectionFuture;
};
