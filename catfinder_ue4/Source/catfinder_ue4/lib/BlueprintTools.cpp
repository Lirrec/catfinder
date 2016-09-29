
#include "catfinder_ue4.h"
#include "BlueprintTools.h"



namespace BPTools {

	void CallActorFunc(UObject * c, const FString& funcName)
	{
		FOutputDeviceNull ar;
		c->CallFunctionByNameWithArguments(*funcName, ar, NULL, true);
	}

	void CallActorFuncIntParam(UObject * c, const FString& funcName, int32 f)
	{
		FString cmd = FString::Printf(TEXT("%s %d"), *funcName, f);
		CallActorFunc(c, cmd);
	}

	void CallActorFuncBoolParam(UObject * c, const FString& funcName, bool b)
	{
		FString cmd = FString::Printf(TEXT("%s %d"), *funcName, b);
		CallActorFunc(c, cmd);
	}
	
	void CallActorFuncFloatParam(UObject * c, const FString& funcName, float f)
	{
		FString cmd = FString::Printf(TEXT("%s %f"), *funcName, f);
		//UE_LOG(LogTemp, Warning, TEXT("call: %s"), *cmd);
		CallActorFunc(c, cmd);
	}

	void CallActorFuncFloatIntParam(UObject * c, const FString& funcName, float f, int32 n)
	{
		FString cmd = FString::Printf(TEXT("%s %f %d"), *funcName, f, n);
		CallActorFunc(c, cmd);
	}
}
