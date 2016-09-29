// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NAOConstants.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NAOBlueprintFunctionLibrary.generated.h"


/**
 * 
 */
UCLASS()
class CATFINDER_UE4_API UNAOBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/*UPROPERTY(BlueprintReadWrite, Category = "NAO")
	static FString NAOIP = TEXT("192.168.1.13");
	*/

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static UNAOSession* getNAOInterface(FString ipAddress);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void initializeNAOInterfaces();

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void shutdownNAOInterfaces();



	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void text2SpeechSay(UNAOSession* session, FString message = TEXT("Test!"));

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void angleInterpolation(UNAOSession* session, FString targetJoint, float degrees, float time, bool isAbsolute = true);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static int getTemperature(UNAOSession* session, FString deviceName);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void moveTo(UNAOSession* session, float xDistanceInMeters, float yDistanceInMeters, float thetaInRadians);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void moveToward(UNAOSession* session, float xSpeedRelative, float ySpeedRelative, float thetaSpeedRelative);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void stopMove(UNAOSession* session);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static int getALMemoryInt(UNAOSession* session, FString key);


	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void setALMemoryString(UNAOSession* session, FString key, FString value);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static FString getALMemoryString(UNAOSession* session, FString key);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void startStream(UNAOSession* session, FString myIP);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void stopStream(UNAOSession* session);
};
