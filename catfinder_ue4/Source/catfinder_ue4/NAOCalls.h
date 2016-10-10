#pragma once

#include "catfinder_ue4.h"

#include "NaoBlueprintFunctionLibrary.h"

class NAOCalls
{
public:
	NAOCalls() {};
	void setSession(std::shared_ptr<qi::Session> s) { session = s; }

	void text2SpeechSay		(	FString message = TEXT("Test!")	);

	void angleInterpolation	(	FString targetJoint,
								float degrees,
								float time,
								bool isAbsolute = true			);

	void angleInterpolation(qi::AnyValue targetJoint,
		qi::AnyValue degrees,
		qi::AnyValue time,
		bool isAbsolute = true);
		
	int getTemperature		(	FString deviceName				);

	void moveTo				(	float xDistanceInMeters,
								float yDistanceInMeters, 
								float thetaInRadians			);

	void moveToward			(	float xSpeedRelative,
								float ySpeedRelative,
								float thetaSpeedRelative		);

	void stopMove			(									);

	int getALMemoryInt		(	FString key						);

	void setALMemoryString	(	FString key, FString value		);
	FString getALMemoryString(	FString key						);

	void launchProgram		(	FString name					);

	void goToPosture		(	FString name					);
	FString getPosture();

	/**
	 * Subscribe to any Module derived from ALExtractor. Those modules typically need to be subscribed to to enable their corresponding sensors.
	 */
	void subscribeToExtractor(FString name);

	void unsubscribeFromExtractor(FString name);

	std::vector<float> getLeftSonarValues();
	std::vector<float> getRightSonarValues();


	void setAutonomousState(ENAOALState newState);

private:
	
	template <class ... Ts>
	void postService(const std::string& serviceName, const std::string& operation, Ts&& ... args);

	template <class R, class ... Ts>
	R callService(const std::string& serviceName, const std::string& operation, Ts&& ... args);

	template <class R>
	R getALMemory(FString key);

	template <class T>
	void setALMemory(FString key, T&& value);

	std::shared_ptr<qi::Session> session;
};