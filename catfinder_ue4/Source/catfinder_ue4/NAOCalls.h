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
								float rad,
								float time,
								bool isAbsolute = true			);

	void angleInterpolation(qi::AnyValue targetJoint,
		qi::AnyValue rad,
		qi::AnyValue time,
		bool isAbsolute = true);
	
	void angleInterpolationWithSpeed(FString targetJoint, float rad, float speed);
		
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

	void setWholeBodyEnabled(bool state);

	void setEnableEffectorControl(FString effectorName, bool state);

	void setEffectorControl(FString effectorName, FVector Coord);

	/**
	 * @param position x,y,z, in meters
	 * @param orientation wx,wy,wz in rad
	 */
	void setPositions(std::vector<std::string> effectorNames, ENAOFRAMES frame, FVector position, FVector orientation, float fractionMaxSpeed = 0.5f);

	/**
	 * Calls ALMotion.rest. Puts the robot into a 'rest' state where no stiffness or power is applied to its joints
	 */
	void rest();

	void playWebAudioStream(FString url, float volume, float balance);

	void stopAllAudioSources();

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