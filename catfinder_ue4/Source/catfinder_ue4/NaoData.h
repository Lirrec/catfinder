// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NAOConstants.h"
#include "TemperatureReading.h"
#include "NAOData.generated.h"

class UNAOSession;

UCLASS(BlueprintType)
class CATFINDER_UE4_API UNAOData : public UObject
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "NAO Data")
	UTemperatureReading* getTemperature(FString device) const;

	UFUNCTION(BlueprintCallable, Category = "NAO Data")
	const TArray<UTemperatureReading*>& getTemperatures() const;

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

	UPROPERTY(BlueprintReadOnly)
	FString version;

	UPROPERTY(BlueprintReadOnly)
	FString robotName;

	UPROPERTY(BlueprintReadOnly)
	FString connectionState;

private:
	friend class UNAODataCollector;

	void sortData();

	UPROPERTY()
	TArray<UTemperatureReading*> TemperatureList;
};
