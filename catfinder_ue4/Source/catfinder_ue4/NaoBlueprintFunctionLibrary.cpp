// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NaoBlueprintFunctionLibrary.h"

#include <qi/session.hpp>
#include <qi/applicationsession.hpp>

	

void UNaoBlueprintFunctionLibrary::test() {

	try {
		qi::Session session; 
		session.connect("tcp://192.168.1.13");
		qi::AnyObject tts = session.service("ALTextToSpeech");
		tts.call<void>("say", std::string("test"));
		session.close();
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}



