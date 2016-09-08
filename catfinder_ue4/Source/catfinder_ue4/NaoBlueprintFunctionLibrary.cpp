// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NaoBlueprintFunctionLibrary.h"

#include <qi/session.hpp>
#include <qi/applicationsession.hpp>

	

void UNaoBlueprintFunctionLibrary::test(FString naoIP) {

	try {
		qi::Session session; 
		session.connect(TCHAR_TO_UTF8(*naoIP));
		// Test #1
		/*qi::AnyObject tts = session.service("ALTextToSpeech");
		tts.call<void>("say", std::string("test"));
		session.close();*/
		// Test #2
		qi::AnyObject tts = session.service("ALMotion");
		tts.call<void>("setStiffnesses", "Head", 1.0f);
		tts.call<void>("angleInterpolation", "HeadYaw", 1.0f, 1.0f, true);
		tts.call<void>("angleInterpolation", "HeadYaw", 0.0f, 2.0f, true);
		//tts = session.service("ALTextToSpeech");
		//tts.call<void>("say", "Nope!");
		session.close();
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}

void UNaoBlueprintFunctionLibrary::text2SpeechSay(FString message, FString naoIP) {
	try {
		qi::Session session;
		session.connect(TCHAR_TO_UTF8(*naoIP));
		qi::AnyObject tts = session.service("ALTextToSpeech");
		tts.call<void>("say",TCHAR_TO_UTF8(*message));
		session.close();
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}

void UNaoBlueprintFunctionLibrary::angleInterpolation(FString targetJoint, float degrees, float time, bool isAbsolute, FString naoIP) {
	try {
		qi::Session session;
		session.connect(TCHAR_TO_UTF8(*naoIP));
		qi::AnyObject tts = session.service("ALMotion");
		tts.call<void>("angleInterpolation", TCHAR_TO_UTF8(*targetJoint), degrees, time, isAbsolute);
		session.close();
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}

void UNaoBlueprintFunctionLibrary::moveTo(float xDistanceInMeters, float yDistanceInMeters, float thetaInRadians, FString naoIP) {
	try {
		qi::Session session;
		session.connect(TCHAR_TO_UTF8(*naoIP));
		qi::AnyObject tts = session.service("ALMotion");
		tts.call<void>("moveTo", xDistanceInMeters, yDistanceInMeters, thetaInRadians);
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}
//qi::Session UNaoBlueprintFunctionLibrary::getSession(FString naoIP) {

	//return NULL;
//}