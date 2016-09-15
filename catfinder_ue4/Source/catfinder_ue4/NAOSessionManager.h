// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "NAOSession.h"

/**
 * 
 */
class CATFINDER_UE4_API NAOSessionManager
{
private:
	static NAOSessionManager* _instance;

	NAOSessionManager();
	~NAOSessionManager();

public:
	static NAOSessionManager* instance();
	UNAOSession* getSession(FString ip);
	// clean up all Sessions, should be called on gameplay end
	void reset();

	TMap<FString, UNAOSession*> sessionMap;
};
