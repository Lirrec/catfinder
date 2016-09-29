// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NAOEventManager.h"
#include "NAOConstants.h"


void NAOEventManager::registerInitialEvents() {
	if (!session->isConnected()) return;
	for (auto eventName : relevantEventNames)
		NAOEventManager::createCallback(eventName);
}

void NAOEventManager::registerAllEvents() {
	if (!session->isConnected()) return;
	qi::AnyObject alm = session->service("ALMemory");
	std::vector<std::string> eventList =alm.call<std::vector<std::string>>("getEventList");
	for (auto eventName : eventList)
		NAOEventManager::createCallback(eventName);

}


//Creates a callback for a specified event that will add an entry to a member-List containing the name of the event.
//For a full list of possible events, see http://doc.aldebaran.com/2-1/naoqi-eventindex.html
void NAOEventManager::createCallback(std::string eventName) {
	try {
		qi::AnyObject alm = session->service("ALMemory");
		qi::AnyObject subscriber = alm.call<qi::AnyObject>("subscriber", eventName);
		//Create a SignalSubscriber that will handle callbacks From NAO
		qi::SignalSubscriber sigSub(qi::AnyFunction::fromDynamicFunction(boost::bind(&NAOEventManager::eventCallback, this, eventName, _1)));
		//The signal created by the subscribe function will Always be called 'signal'
		qi::Future<qi::SignalLink> futureLink = subscriber.connect("signal", sigSub);

		futureLink.wait();
		if (futureLink.hasError()) {
			UE_LOG(LogTemp, Error, TEXT("Error on Signal connect: '%s'"), ANSI_TO_TCHAR(futureLink.error().c_str()));
		}
		//If the subscriber object isn't stored, the callback will no longer happen
		subscriberList.push_back(subscriber);
		UE_LOG(LogTemp, Warning, TEXT("Signal for Event '%s' connected"), ANSI_TO_TCHAR(eventName.c_str()));
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}

//simple callback, writing message to UE-Logs and adding the event to a membered list when called
qi::AnyReference  NAOEventManager::eventCallback(std::string eventName, const std::vector<qi::AnyReference>& params) {
	UE_LOG(LogTemp, Warning, TEXT("NAOEvent: '%s'"), ANSI_TO_TCHAR(eventName.c_str()));
	//eventMap.insert(std::make_pair(std::string(TCHAR_TO_UTF8(*eventName)), params));
	if (eventQueue.size() >= EVENT_QUEUE_SIZE)
		eventQueue.pop_front();
	eventQueue.push_back(eventName);
	//returntype needs to be anyreference. this solution was taken form official libqi examples
	return qi::AnyReference();
}