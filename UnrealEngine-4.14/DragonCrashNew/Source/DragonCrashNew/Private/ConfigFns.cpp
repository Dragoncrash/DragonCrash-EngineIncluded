// Fill out your copyright notice in the Description page of Project Settings.

#include "DragonCrashNew.h"
#include "ConfigFns.h"


void UConfigFns::ReadCustomConfig(const FString& filename, const FString& section, const FString& var, FString& out_value, bool& out_valid, FString& out_filepath) {

	//Config handler is GConfig I think...
	if (!GConfig) return;
	checkFileIOEnabled();

	FString filepath = FPaths::Combine(FPaths::GameConfigDir(), filename);
	out_filepath = filepath;
	out_valid = true;
	if (!FPaths::FileExists(filepath)) {
		FString cleanname = FPaths::GetCleanFilename(filepath);
		GConfig->LoadGlobalIniFile(cleanname, *FPaths::GetBaseFilename(filepath), NULL, true);
	}

	if (GConfig->DoesSectionExist(*section, filepath)) {
		GConfig->GetString(*section, *var, out_value, filepath);
	}
	else out_valid = false;

}

void UConfigFns::WriteCustomConfig(const FString& filename, const FString& section, const FString& var, const FString& value) {
	
	if (!GConfig) return;
	checkFileIOEnabled();

	FString filepath = FPaths::Combine(FPaths::GameConfigDir(), filename);

	//Create config if it does not exist and reload values
	if (!FPaths::FileExists(filepath)) {
		FString cleanname = FPaths::GetCleanFilename(filepath);
		GConfig->LoadGlobalIniFile(cleanname,*FPaths::GetBaseFilename(filepath),NULL,true);
	}
	
	//File exists so modify the values
	GConfig->SetString(*section, *var, *value, filepath);

	//Force Flush buffers
	GConfig->Flush(false, filepath);

}

void UConfigFns::ReadEngineConfig(const FString & section, const FString & var, FString & out_value, bool & out_valid)
{
	if (!GConfig) return;
	checkFileIOEnabled();

	out_valid = true;
	if (GConfig->DoesSectionExist(*section, GEngineIni)) {
		GConfig->GetString(*section, *var, out_value, GEngineIni);
	}
	else out_valid = false;
}

void UConfigFns::WriteEngineConfig(const FString & section, const FString & var, const FString & value)
{
	if (!GConfig) return;
	checkFileIOEnabled();

	FString filepath = FPaths::Combine(FPaths::GameUserDir(), GEngineIni);

	//File exists so modify the values
	GConfig->SetString(*section, *var, *value, GEngineIni);

	//Force Flush buffers
	GConfig->Flush(false, GEngineIni);
}


void UConfigFns::checkFileIOEnabled() {
	if (GConfig->AreFileOperationsDisabled()) GConfig->EnableFileOperations();
}