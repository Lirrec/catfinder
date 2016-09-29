// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <array>
#include <memory>
#include <list>

#include "NAODataCollector.h"
#include "NAOEventManager.h"
#include "NAOCalls.h"

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


	NAOCalls& getAPI() {
		return api;
	}

	UFUNCTION(BluePrintCallable, Category = "NAO Interface")
	ENAOIState getState();
	
	UFUNCTION(BluePrintCallable, Category = "NAO Interface")
	void connect(FString ip);

	UFUNCTION(BluePrintCallable, Category = "NAO Interface")
	void disconnect();
	
	UFUNCTION(BluePrintCallable, Category = "NAO Interface")
	UNAOData* getData();

	UFUNCTION(BluePrintCallable, Category = "NAO Interface")
		void updateData();

	/** Creates a callback for a specified event that will add an entry to a member-List containing the name of the event.
	For a full list of possible events, see http://doc.aldebaran.com/2-1/naoqi-eventindex.html
	*/
	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		void createCallback(FString eventName = TEXT("ChestButtonPressed"));


private:

	bool isConnected();

	ENAOIState State = ENAOIState::disconnected;

	std::shared_ptr<qi::Session> session;

	UPROPERTY()
	UNAODataCollector* dataCollector;
	NAOEventManager  evtMgr;
	NAOCalls		 api;
	
	UPROPERTY()
	UNAOData* Data;
	
	FString NAOIP;

	qi::Future<void> connectionFuture;

};
