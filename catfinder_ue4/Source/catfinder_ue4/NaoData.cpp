// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NAOData.h"


UTemperatureReading* UNAOData::getTemperature(FString device) const {
	for (auto d : TemperatureList) {
		if (d->Joint.Equals(device)) return d;
	}
	return nullptr;
}

const TArray<UTemperatureReading*>& UNAOData::getTemperatures() const {
	return TemperatureList;
}

void UNAOData::sortData() {
	TemperatureList.Sort([](const auto& a, const auto& b) {
		return a.Temperature > b.Temperature;
	});
}