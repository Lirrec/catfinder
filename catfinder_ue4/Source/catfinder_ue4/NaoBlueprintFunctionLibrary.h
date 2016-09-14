// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NaoBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CATFINDER_UE4_API UNaoBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/*UPROPERTY(BlueprintReadWrite, Category = "NAO")
	static FString naoIP = TEXT("192.168.1.13");
	*/

	UFUNCTION(BlueprintCallable, Category = "NAO")
	static void test(FString naoIP = TEXT("192.168.1.13"));
	
	UFUNCTION(BlueprintCallable, Category = "NAO")
	static void text2SpeechSay(FString message = TEXT("Test!"), FString naoIP = TEXT("192.168.1.13"));

	UFUNCTION(BlueprintCallable, Category = "NAO")
		static int getTemperature(FString deviceName = TEXT("Head"), FString naoIP = TEXT("192.168.1.13"));
	
	UFUNCTION(BlueprintCallable, Category = "NAO")
	static void angleInterpolation(FString targetJoint, float degrees, float time, bool isAbsolute = true, FString naoIP = TEXT("192.168.1.13"));

	//Should look at moveToward, comments say its whats supposed to be used w/ joysticks etc.
	UFUNCTION(BlueprintCallable, Category = "NAO")
		static void moveTo(float xDistanceInMeters, float yDistacneInMeters, float thetaInRadians, FString naoIP = TEXT("192.168.1.13"));

	UFUNCTION(BlueprintCallable, Category = "NAO")
		static int getALMemoryInt(FString key, FString naoIP = TEXT("192.168.1.13"));


//private:
		//static qi::Session getSession(FString naoIP);
};
