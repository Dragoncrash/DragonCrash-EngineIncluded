// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "GameLiftServerSDK.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "OnlineMultiplayerFunctions.generated.h"

/**
 * 
 */
UCLASS()
class DRAGONCRASH_API UOnlineMultiplayerFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "DragonCrashMultiplayer")
	static void GameLiftMultiplayerActivate();
};
