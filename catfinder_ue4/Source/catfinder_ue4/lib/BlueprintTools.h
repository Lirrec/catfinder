#pragma once

#include "Runtime/Core/Public/Containers/UnrealString.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

namespace BPTools {
	void CallActorFunc(UObject * c, const FString&);
	void CallActorFuncIntParam(UObject * c, const FString&, int32 f);
	void CallActorFuncBoolParam(UObject * c, const FString&, bool b);
	void CallActorFuncFloatParam(UObject * c, const FString&, float f);
	void CallActorFuncFloatIntParam(UObject * c, const FString&, float f, int32 n);
}