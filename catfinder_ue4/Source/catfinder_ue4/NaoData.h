// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NAOConstants.h"
#include "NAOData.generated.h"

class UNAOSession;

UCLASS()
class CATFINDER_UE4_API UNAOData : public UObject
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="NAO Data")
	int getTemperature(FString device) const;

	UFUNCTION(BlueprintCallable, Category = "NAO Data")
	const TArray<int32> getTemperatures() const;
	

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
	friend class UNAOSession;
	TMap<FString, int32> temperatures;
};
