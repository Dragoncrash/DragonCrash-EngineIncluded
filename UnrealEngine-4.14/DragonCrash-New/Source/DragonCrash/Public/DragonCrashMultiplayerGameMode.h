// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameLiftServerSDK.h"

#include "GameFramework/GameModeBase.h"
#include "DragonCrashMultiplayerGameMode.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(DragonCrashDedicatedServer, Log, All);

/**
 * 
 */
UCLASS()
class DRAGONCRASH_API ADragonCrashMultiplayerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ADragonCrashMultiplayerGameMode(const FObjectInitializer& ObjectInitializer);

	void OnStartGameSession(Aws::GameLift::Server::Model::GameSession GameLiftSession);
	void OnTerminate();
	bool OnHealthCheck();

	void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);
	FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT(""));
	void Logout(AController* Exiting);
private:
	FGameLiftServerSDKModule* GameLiftSdkModule;
	bool IsTeamGame = false;
	TMap<AController*, FString> PlayerSessionIds;
};
