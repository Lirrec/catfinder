// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NaoBlueprintFunctionLibrary.h"

#include <qi/session.hpp>
#include <qi/future.hpp>
#include "NAOSessionManager.h"


UNAOSession* UNaoBlueprintFunctionLibrary::getNaoInterface(FString ipAddress) {
	return NAOSessionManager::instance()->getSession(ipAddress);
}

void UNaoBlueprintFunctionLibrary::initializeNAOInterfaces() {
	NAOSessionManager::instance()->getSession(TEXT("192.168.1.13"));
}

void UNaoBlueprintFunctionLibrary::shutdownNAOInterfaces() {
	NAOSessionManager::instance()->reset();
}