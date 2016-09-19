// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "SliderBase.h"


// Sets default values
ASliderBase::ASliderBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASliderBase::BeginPlay()
{
	Super::BeginPlay();
	OnValueChanged.Broadcast(SliderValue);
}

// Called every frame
void ASliderBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

float ASliderBase::GetValue() {
	return SliderValue;
}

void ASliderBase::SetValue(float val) {
	//UE_LOG(LogTemp, Warning, TEXT("Slider SetValue %f"), val);
	SliderValue = val;
	OnValueChanged.Broadcast(val);
}