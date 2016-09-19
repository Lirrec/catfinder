// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NAOData.h"


int UNAOData::getTemperature(FString device) const {
	if (Temperatures.Contains(device)) return Temperatures[device];
	return -1;
}