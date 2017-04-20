// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConfigFns.generated.h"

/**
 * 
 */
UCLASS(Config=Engine)
class DRAGONCRASHNEW_API UConfigFns : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Config")
	static void ReadCustomConfig(const FString& filename, const FString& section, const FString& var, FString& out_value, bool& out_valid, FString& out_filepath);

	UFUNCTION(BlueprintCallable, Category = "Config")
	static void WriteCustomConfig(const FString& filename, const FString& section, const FString& var, const FString& value);

	UFUNCTION(BlueprintCallable, Category = "Config")
	static void ReadEngineConfig(const FString& section, const FString& var, FString& out_value, bool& out_valid);

	UFUNCTION(BlueprintCallable, Category = "Config")
	static void WriteEngineConfig(const FString& section, const FString& var, const FString& value);
	
	//Added a GET function for GEngineIni for compatibility [DEPRECATED]
	//UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Config")
	//static FString getEngineConfigFilePath();
	
	static void checkFileIOEnabled();
};
