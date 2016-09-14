// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <qi/session.hpp>
#include <qi/future.hpp>
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
	static NAOSessionManager* Instance();
	std::shared_ptr<qi::Session> getSession(std::string ip);
};
