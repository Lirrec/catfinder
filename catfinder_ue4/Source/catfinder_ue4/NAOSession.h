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

	//Creates a callback for a specified event that will add an entry to a member-List containing the name of the event.
	//For a full list of possible events, see http://doc.aldebaran.com/2-1/naoqi-eventindex.html
	UFUNCTION(BlueprintCallable, Category = UE_NAO_CATEGORY)
		void createCallback(FString eventName = TEXT("ChestButtonPressed"));

private:

	bool isConnected();
	void updateAsyncResults();

	ENAOIState State = ENAOIState::disconnected;

	UPROPERTY()
	TArray<UNAOData*> Data;
	
	FString NaoIP;
	std::shared_ptr<qi::Session> session;

	std::list<qi::Future<void>> AsyncCalls;
	qi::Future<void> connectionFuture;

	float lastUpdate;
	float updateDelay;
	void getTemperatures();
	qi::Future<std::vector<int>> temperatureResult;

	//simple callback, writing message to UE-Logs and adding the event to a membered list when called
	qi::AnyReference eventCallback(FString eventName, const std::vector<qi::AnyReference>& params);
	std::list<qi::AnyObject> subscriberList;
	std::map<std::string, std::vector<qi::AnyReference>> eventMap;
};
