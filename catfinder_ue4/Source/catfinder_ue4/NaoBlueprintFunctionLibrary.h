// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NAOConstants.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NAOBlueprintFunctionLibrary.generated.h"



UENUM(BlueprintType)
enum class ENAOALState : uint8 {
	solitary UMETA(DisplayName = "active, but not moving or interacting"),
	interactive UMETA(DisplayName = "interacting with any persons"),
	disabled UMETA(DisplayName = "not active")
};

UENUM(BluePrintType)
enum class ENAOFRAMES : uint8 {
	torso = 0 UMETA(DisplayName = "Frame Torso (origin in the center of the torso)"),
	world UMETA(DisplayName = "Frame World (constant origin which is set at boot/startup)"),
	robot UMETA(DisplayName = "Frame Robot (origin is the average of both feet positions)")
};

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
		static bool isConnected(UNAOSession* session);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void text2SpeechSay(UNAOSession* session, FString message = TEXT("Test!"));


	/* rotates a specified joint a number of radians within a timeframe. 
		Unit for the Timeframe is seconds.
		If isAbsolute is true, the basic angle for the rotation will be the 0-stance of the joint.
	*/
	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void angleInterpolation(UNAOSession* session, FString targetJoint, float rad, float time, bool isAbsolute = true);

	// Rotates a specified joint a number of radians at a fraction of the Joints maximum rotational speed.
	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void angleInterpolationWithSpeed(UNAOSession* session, FString targetJoint, float rad, float speed = 1.0);

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

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void moveHeadToZeroPosition(UNAOSession* session);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void setAutonomousState(UNAOSession* session, ENAOALState state);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void goToPosture(UNAOSession* session, FString name);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void registerInitialEvents(UNAOSession* session);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static FString getOneEvent(UNAOSession* session);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static FString dateToString(FDateTime time);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
	static void setWholeBodyEnabled(UNAOSession* session, bool state);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
	static void setEnableEffectorControl(UNAOSession* session, FString effectorName, bool state);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
	static void setEffectorControl(UNAOSession* session, FString effectorName, FVector position);


	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
	static void setPositions(UNAOSession* session, FString effectorName, ENAOFRAMES frame, FVector position, FVector orientation, float fractionMaxSpeed = 0.5f);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
	static void rest(UNAOSession* session);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void playWebAudioStream(UNAOSession* session, FString url, float volume = 1, float balance = 0);

	UFUNCTION(BlueprintCallable, Category = "NAO Interface")
		static void stopAllAudioSources(UNAOSession* session);
};
