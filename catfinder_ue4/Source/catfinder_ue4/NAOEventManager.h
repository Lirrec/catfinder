// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "catfinder_ue4.h"

class CATFINDER_UE4_API NAOEventManager
{
public:
	NAOEventManager() {};
	void setSession(std::shared_ptr<qi::Session> s) { session = s; }
	void registerAllEvents();
	void registerInitialEvents();

	//Creates a callback for a specified event that will add an entry to a member-List containing the name of the event.
	//For a full list of possible events, see http://doc.aldebaran.com/2-1/naoqi-eventindex.html
	void createCallback(std::string eventName);
private:
	std::shared_ptr<qi::Session> session;

	//simple callback, writing message to UE-Logs and adding the event to a membered list when called
	qi::AnyReference eventCallback(std::string eventName, const std::vector<qi::AnyReference>& params);

	std::list<qi::AnyObject> subscriberList;

	std::map<std::string, std::vector<qi::AnyReference>> eventMap;
	std::deque<std::string> eventQueue;

};
