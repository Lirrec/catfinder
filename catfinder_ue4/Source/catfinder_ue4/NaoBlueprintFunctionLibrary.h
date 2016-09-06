// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NaoBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CATFINDER_UE4_API UNaoBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Test")
	static void test();
	
	
};
