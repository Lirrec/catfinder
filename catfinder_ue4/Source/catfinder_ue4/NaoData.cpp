// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NAOData.h"


int UNAOData::getTemperature(FString device) const {
	if (temperatures.Contains(device)) return temperatures[device];
	return -1;
}

const TArray<int32> UNAOData::getTemperatures() const {
	TArray<int32> re;
	for (auto& Elem : temperatures) {
		re.Add(Elem.Value);
	}
	return re;
}