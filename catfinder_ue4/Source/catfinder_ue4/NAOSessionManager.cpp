// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include <map>
#include <qi/session.hpp>
#include "NAOSessionManager.h"

NAOSessionManager* NAOSessionManager::_instance = nullptr;

NAOSessionManager::NAOSessionManager()
{
}

NAOSessionManager::~NAOSessionManager()
{
}

NAOSessionManager* NAOSessionManager::instance() {
	if(!NAOSessionManager::_instance) {
		NAOSessionManager::_instance = new NAOSessionManager();
	}
	return NAOSessionManager::_instance;
}

/** Returns a shared_ptr to a NAOSession which is succesfully connected to a provided IP.
	Returns NULL if there's an error during the connecting process.
*/
UNAOSession* NAOSessionManager::getSession(FString ip) {
	if (!sessionMap.Contains(ip)) {
		
		auto session = NewObject<UNAOSession>();
		session->AddToRoot();
		session->connect(ip);

		//if (session->getState() != ENAOIState::connected)
		//	return nullptr;
		
		sessionMap.Add(ip,session);
	}
	return sessionMap[ip];
	//return NULL;
}

void NAOSessionManager::reset() {
	sessionMap.Reset();
}