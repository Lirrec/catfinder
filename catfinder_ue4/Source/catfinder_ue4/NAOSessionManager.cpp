// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NAOSessionManager.h"

NAOSessionManager* NAOSessionManager::_instance = NULL;

std::map<std::string, std::shared_ptr<qi::Session>> mapSessions;

NAOSessionManager::NAOSessionManager()
{
}

NAOSessionManager::~NAOSessionManager()
{
}

NAOSessionManager* NAOSessionManager::Instance() {
	if(!NAOSessionManager::_instance) {
		NAOSessionManager::_instance = new NAOSessionManager();
	}
	return NAOSessionManager::_instance;
}
/** Returns a shared_ptr to a libQI Session which is succesfully connected to a provided IP.
	Returns NULL if there's an error during the connecting process.
*/
std::shared_ptr<qi::Session> NAOSessionManager::getSession(std::string ip) {
	if (!mapSessions.count(ip)) {
		//mapSessions[ip];
		std::shared_ptr<qi::Session> session(new qi::Session);
		try {
			qi::Future<void> future = session->connect(ip);
			future.wait();
			if (future.hasError()) {
				UE_LOG(LogTemp, Warning, TEXT("Future error %s"), ANSI_TO_TCHAR(future.error().c_str()));
				return NULL;
			}
		}
		catch (const std::exception& e) {
			UE_LOG(LogTemp, Warning, TEXT("std Exception: %s"), ANSI_TO_TCHAR(e.what()));
			//mapSessions.erase(ip);
			return NULL;
		}
		mapSessions.insert(std::pair<std::string,std::shared_ptr<qi::Session>>(ip,session));
	}
	return mapSessions.at(ip);
	//return NULL;
}