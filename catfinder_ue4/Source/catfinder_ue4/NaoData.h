// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NAOData.generated.h"

UCLASS()
class CATFINDER_UE4_API UNaoData : public UObject
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="NAO Data")
	int getTemperature(FString device) const;

	UPROPERTY(BlueprintReadOnly)
	int ping;

	UPROPERTY(BlueprintReadOnly)
	int ramUsed;

	UPROPERTY(BlueprintReadOnly)
	int ramAvailable;

	UPROPERTY(BlueprintReadOnly)
	int batteryPercentage;

	UPROPERTY(BlueprintReadOnly)
	int cpuLoad;

private:
	TMap<FString, int32> Temperatures;
};
