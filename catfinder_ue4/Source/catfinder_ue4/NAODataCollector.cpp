// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NAODataCollector.h"

UNAOData* UNAODataCollector::getData() {
	if (data.Num() == 0) data.Push(NewObject<UNAOData>());
	return data.Top();
}

void UNAODataCollector::updateData() {
	/*UWorld* const world = GetWorld();
	if (world) {
	if (lastUpdate + updateDelay < world->RealTimeSeconds) {

	}
	}*/
	if (!session->isConnected()) return;
	getTemperatures();
}



void UNAODataCollector::getTemperatures() {
	if (temperatureResult.isValid()) {

		if (!temperatureResult.isFinished()) return;

		if (temperatureResult.hasError()) {
			UE_LOG(LogTemp, Warning, TEXT("QI Future Error: %s"), ANSI_TO_TCHAR(temperatureResult.error().c_str()));
			return;
		}

		UNAOData* data = getData();

		if (!data) return;
		data->TemperatureList.Reset();


		std::vector<int> temps = temperatureResult.value();

		int idx = 0;
		for (int temp : temps) {

			UTemperatureReading* reading = NewObject<UTemperatureReading>();
			reading->Joint = ANSI_TO_TCHAR(sensorNames[idx++].c_str());
			reading->Temperature = temp;
			data->TemperatureList.Add(reading);
			data->sortData();
			//UE_LOG(LogTemp, Warning, TEXT("Temp: %s %i"), ANSI_TO_TCHAR(sensorNames[idx++].c_str()), temp);
		}

		if (idx > 0)
			UE_LOG(LogTemp, Warning, TEXT("Received new %i temperatures"), idx);

		temperatureResult = qi::Future<std::vector<int>>();
	}
	else {
		if (!session->isConnected()) return;
		std::vector<std::string> temperatureSensorNames;
		temperatureSensorNames.reserve(sensorNames.size());

		for (const auto& joint : sensorNames) {
			temperatureSensorNames.push_back("Device/SubDeviceList/" + joint + "/Temperature/Sensor/Value");
		}

		// no valid future, check if we should start the next call
		// TODO: actually check based on some Timer
		try {
			qi::AnyObject alm = session->service("ALMemory");
			UE_LOG(LogTemp, Warning, TEXT("before first call"));

			alm.post("getListData", temperatureSensorNames);

			auto r = alm.call<std::vector<int>>("getListData", temperatureSensorNames);

			UE_LOG(LogTemp, Warning, TEXT("after call, before async"));

			//text2SpeechSay(TEXT("k"));

			auto f = alm.async<std::vector<int>>("getListData", temperatureSensorNames);
			f.connect([](auto) { UE_LOG(LogTemp, Warning, TEXT("callback")); });

			temperatureResult = alm.async<std::vector<int>>("getListData", temperatureSensorNames);
			UE_LOG(LogTemp, Warning, TEXT("async finished"));
		}
		catch (std::exception& e) {
			UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
		}
	}
}
