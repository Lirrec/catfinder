// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"

#include <algorithm>


#include "NAOData.h"
#include "NAOSession.h"

UNAOSession::UNAOSession()
{
	session = std::make_shared<qi::Session>();
	dataCollector = NewObject<UNAODataCollector>();

	api.setSession(session);
	evtMgr.setSession(session);
	dataCollector->setSession(session);
}

ENAOIState UNAOSession::getState() {
	return State;
}



void UNAOSession::connect(FString ip) {

	NAOIP = ip;

	try {
		State = ENAOIState::connecting;
		connectionFuture = session->connect(TCHAR_TO_UTF8(*NAOIP));
		
		UE_LOG(LogTemp, Warning, TEXT("NAOSession connecting to %s"), *NAOIP);
		State = ENAOIState::connecting;
		NAOIP = NAOIP;
	}
	catch (const std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("Exception while connecting: %s"), ANSI_TO_TCHAR(e.what()));
		State = ENAOIState::disconnected;
		return;
	}
}

void UNAOSession::disconnect() {
	UE_LOG(LogTemp, Warning, TEXT("NAOSession disconnecting from %s"), ANSI_TO_TCHAR(session->url().str().c_str()));
	session->close();
	State = ENAOIState::disconnected;
}

bool UNAOSession::isConnected() {
	if (session && State == ENAOIState::connecting) {
		if (connectionFuture.isFinished()) {
			if (connectionFuture.hasError()) {
				UE_LOG(LogTemp, Error, TEXT("NAOSession failed to connect: '%s'"), ANSI_TO_TCHAR(connectionFuture.error().c_str()));
				State = ENAOIState::disconnected;
				return false;
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("NAOSession successfully connected: '%s'"), ANSI_TO_TCHAR(session->url().str().c_str()));
				State = ENAOIState::connected;
				return true;
			}
		}

		UE_LOG(LogTemp, Warning, TEXT("NAO Session still connecting"));
		return false;
	}

	if (!session || !session->isConnected() ) {
		UE_LOG(LogTemp, Warning, TEXT("NAO Session not connected"));
		State = ENAOIState::disconnected;
		return false;
	}
	return true;
}

UNAOData* UNAOSession::getData() {
	return dataCollector->getData();
}

void UNAOSession::createCallback(FString eventName) {
	evtMgr.createCallback(TCHAR_TO_ANSI(*eventName));
	//evtMgr.registerAllEvents();
}

void UNAOSession::updateData() {
	return dataCollector->updateData();
}