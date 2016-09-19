// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreUObject.h"
#include "GameFramework/Actor.h"
#include "SliderBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FSliderValueDelegate, float);

UCLASS()
class CATFINDER_UE4_API ASliderBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASliderBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Slider")
	float GetValue();

	UFUNCTION(BlueprintCallable, Category = "Slider")
	void SetValue(float val);
	
	//UPROPERTY(BlueprintAssignable, Category = "Slider")
	FSliderValueDelegate OnValueChanged;

private:
	float SliderValue;
};
