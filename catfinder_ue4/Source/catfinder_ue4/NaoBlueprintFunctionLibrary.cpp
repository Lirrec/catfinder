// Fill out your copyright notice in the Description page of Project Settings.

#include "catfinder_ue4.h"
#include "NaoBlueprintFunctionLibrary.h"

#include <qi/session.hpp>
#include <qi/applicationsession.hpp>

	

void UNaoBlueprintFunctionLibrary::test() {
	int argc = 3;
	char* a = "test";
	char* b = "--qi-url";
	char* c = "192.168.1.11";
	char* args[] = { a,b,c };
	char ** argv = &args[0];
	
	//std::string path = "tcp://192.168.1.11";
	//std::string name = "NaoSession";

	try {
		//qi::ApplicationSession app(name, argc, argv, 0, path);
		qi::ApplicationSession app(argc, argv);
		app.startSession(); // connect the session
		qi::SessionPtr session = app.session();

		qi::AnyObject tts = session->service("ALTextToSpeech");
		tts.call<void>("say", std::string("test"));
	}
	catch (std::exception& e) {
		UE_LOG(LogTemp, Warning, TEXT("QI Exception: %s"), ANSI_TO_TCHAR(e.what()));
	}
}



