// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConfigFns.generated.h"

/**
 * 
 */
UCLASS(Config=Engine)
class DRAGONCRASH_API UConfigFns : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Config")
	static void ReadCustomConfig(const FString& section, const FString& var, FString& out_value, bool& out_valid);

	UFUNCTION(BlueprintCallable, Category = "Config")
	static void WriteCustomConfig(FString section, FString var, FString value);
	
	
};
