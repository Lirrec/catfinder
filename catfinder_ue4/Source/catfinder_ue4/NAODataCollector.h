#pragma once

#include "catfinder_ue4.h"

#include <future>

#include "NAODataCollector.generated.h"

UCLASS()
class CATFINDER_UE4_API UNAODataCollector : public UObject
{
	GENERATED_BODY()


public:

	void setSession(std::shared_ptr<qi::Session> s) { session = s; }

	UNAOData* getData();


	void updateData();

	// collects data and stores the result in the dataTmp member
	void collectData();

private:
	UPROPERTY()
	TArray<UNAOData*> data;

	UPROPERTY()
		UNAOData* dataTmp;

	std::shared_ptr<qi::Session> session;
	
	void collectSystemInformation(UNAOData* data);
	void getTemperatures(UNAOData* data);

	std::future<void> collectorFuture;
};
