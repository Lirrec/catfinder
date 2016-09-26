// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "TemperatureReading.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CATFINDER_UE4_API UTemperatureReading : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	int Temperature;

	UPROPERTY(BlueprintReadWrite)
	FString Joint;
	
	
};
