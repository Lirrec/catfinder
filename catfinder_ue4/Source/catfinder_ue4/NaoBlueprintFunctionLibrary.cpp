// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NAOBlueprintFunctionLibrary.h"

#include <qi/session.hpp>
#include <qi/future.hpp>
#include "NAOSessionManager.h"


UNAOSession* UNAOBlueprintFunctionLibrary::getNAOInterface(FString ipAddress) {
	return NAOSessionManager::instance()->getSession(ipAddress);
}

void UNAOBlueprintFunctionLibrary::initializeNAOInterfaces() {
	UE_LOG(LogTemp, Warning, TEXT("NAO: initializing Sessions."));
	//NAOSessionManager::instance()->getSession(TEXT("192.168.1.13"));
	NAOSessionManager::instance()->getSession(TEXT("10.215.255.187"));
}

void UNAOBlueprintFunctionLibrary::shutdownNAOInterfaces() {
	UE_LOG(LogTemp, Warning, TEXT("NAO: resetting Sessions."));
	NAOSessionManager::instance()->reset();
}