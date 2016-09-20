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

	UFUNCTION(BlueprintCallable, Category = UE_NAO_CATEGORY)
		static UNAOSession* getNAOInterface(FString ipAddress);

	UFUNCTION(BlueprintCallable, Category = UE_NAO_CATEGORY)
		static void initializeNAOInterfaces();

	UFUNCTION(BlueprintCallable, Category = UE_NAO_CATEGORY)
		static void shutdownNAOInterfaces();
};
