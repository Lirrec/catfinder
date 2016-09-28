#pragma once

#include "catfinder_ue4.h"
#include "NAODataCollector.generated.h"

UCLASS()
class CATFINDER_UE4_API UNAODataCollector : public UObject
{
	GENERATED_BODY()


public:

	void setSession(std::shared_ptr<qi::Session> s) { session = s; }

	UNAOData* getData();


	void updateData();

private:
	UPROPERTY()
	TArray<UNAOData*> data;

	std::shared_ptr<qi::Session> session;

	float lastUpdate;
	float updateDelay;
	
	void getTemperatures();

	qi::Future<std::vector<int>> temperatureResult;
};
