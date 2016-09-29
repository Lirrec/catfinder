#pragma once

#include "catfinder_ue4.h"

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

private:
	std::shared_ptr<qi::Session> session;
};