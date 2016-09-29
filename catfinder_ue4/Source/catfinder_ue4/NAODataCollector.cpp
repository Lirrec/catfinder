// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"

#include <future>
#include <functional>
#include "NAODataCollector.h"

UNAOData* UNAODataCollector::getData() {
	if (data.Num() == 0) data.Push(NewObject<UNAOData>());
	return data.Top();
}

void UNAODataCollector::updateData() {
	if (!session->isConnected()) return;
	
	using namespace std::chrono_literals;

	if (collectorFuture.valid()) {
		auto state = collectorFuture.wait_for(0s);

		// invalidate the future.
		if (state == std::future_status::ready) { 
			collectorFuture.get();
			if ( dataTmp != nullptr) data.Add(dataTmp);
			dataTmp = nullptr;
		}
	}
	else {
		collectorFuture = std::async(std::launch::async, std::bind(&UNAODataCollector::collectData, this) );
	}




}

void UNAODataCollector::collectData() {
	if (!session->isConnected()) return;

	dataTmp = NewObject<UNAOData>();
	getTemperatures(dataTmp);

	collectSystemInformation(dataTmp);
}


void UNAODataCollector::getTemperatures(UNAOData* data) {
	try {

		if (!data) return;
		data->TemperatureList.Reset();

		std::vector<std::string> temperatureSensorNames;
		temperatureSensorNames.reserve(sensorNames.size());

		for (const auto& joint : sensorNames) {
			temperatureSensorNames.push_back("Device/SubDeviceList/" + joint + "/Temperature/Sensor/Value");
		}

		qi::AnyObject alm = session->service("ALMemory");
		std::vector<int> temps = alm.call<std::vector<int>>("getListData", temperatureSensorNames);

		int idx = 0;
		for (int temp : temps) {
			UTemperatureReading* reading = NewObject<UTemperatureReading>();
			reading->Joint = ANSI_TO_TCHAR(sensorNames[idx++].c_str());
			reading->Temperature = temp;
			data->TemperatureList.Add(reading);
			data->sortData();
			//UE_LOG(LogTemp, Warning, TEXT("Temp: %s %i"), ANSI_TO_TCHAR(sensorNames[idx++].c_str()), temp);
		}
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}

void UNAODataCollector::collectSystemInformation(UNAOData* data) {

	try {
		qi::AnyObject alsystem = session->service("ALSystem");

		int ramFree =		alsystem.call<int>("freeMemory");

		data->ramAvailable = alsystem.call<int>("totalMemory");
		data->ramUsed =		data->ramAvailable - ramFree;

		data->robotName =	FString(alsystem.call<std::string>("robotName").c_str());
		data->version =		FString(alsystem.call<std::string>("systemVersion").c_str());

		qi::AnyObject albattery = session->service("ALBattery");

		data->batteryPercentage = albattery.call<int>("getBatteryCharge");
		
		qi::AnyObject alconman = session->service("ALConnectionManager");
		
		data->connectionState =	FString(alconman.call<std::string>("state").c_str());

		int cpuLoad = 0;


	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}

}