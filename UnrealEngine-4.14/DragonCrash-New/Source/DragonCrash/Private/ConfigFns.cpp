// Fill out your copyright notice in the Description page of Project Settings.

#include "DragonCrash.h"
#include "ConfigFns.h"


void UConfigFns::ReadCustomConfig(const FString& section, const FString& var, FString& out_value, bool& out_valid) {

	//Config handler is GConfig I think...
	if (!GConfig) return;

	out_valid = true;
	GConfig->GetString(*section, *var, out_value, GEngineIni);
	if (out_value.IsEmpty())out_valid = false;

}

void UConfigFns::WriteCustomConfig(FString section, FString var, FString value) {
	
	if (!GConfig) return;
	GConfig->SetString(*section, *var, *value, GEngineIni);

	//Force Flush buffers
	GConfig->Flush(false, GEngineIni);
}

