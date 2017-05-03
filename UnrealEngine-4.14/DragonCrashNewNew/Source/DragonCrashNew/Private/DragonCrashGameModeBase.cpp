// Fill out your copyright notice in the Description page of Project Settings.

#include "DragonCrashNew.h"
#include "DragonCrashGameModeBase.h"


DEFINE_LOG_CATEGORY(DragonCrashDedicatedServer);

ADragonCrashGameModeBase::ADragonCrashGameModeBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_GAMELIFT
	if (!HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
	{
		UE_LOG(DragonCrashDedicatedServer, Log, TEXT("Running GameLift Server SDK Startup"));

		// get the gamelift module
		GameLiftSdkModule = &FModuleManager::LoadModuleChecked<FGameLiftServerSDKModule>(FName("GameLiftServerSDK"));

		// initialize the SDK
		GameLiftSdkModule->InitSDK();

		// bind event handlers
		FProcessParameters* params = new FProcessParameters();
		params->OnStartGameSession.BindUObject(this, &UDragonCrashGameInstance::OnStartGameSession);
		params->OnTerminate.BindUObject(this, &UDragonCrashGameInstance::OnTerminate);
		params->OnHealthCheck.BindUObject(this, &UDragonCrashGameInstance::OnHealthCheck);

		//This game server tells GameLift that it listens on port 7777 for incoming player connections.
		params->port = 7777;

		//Here, the game server tells GameLift what set of files to upload when the game session ends.
		//GameLift uploads everything specified here for the developers to fetch later.
		TArray<FString> logfiles;
		//logfiles.Add(TEXT("aLogFile.txt"));
		params->logParameters = logfiles;

		//Calling ProcessReady tells GameLift this game server is ready to receive incoming game sessions!
		GameLiftSdkModule->ProcessReady(*params);

		UE_LOG(DragonCrashDedicatedServer, Log, TEXT("Finished GameLift Server SDK Startup"));
	}
#endif
}

void ADragonCrashGameModeBase::OnStartGameSession(Aws::GameLift::Server::Model::GameSession GameLiftSession)
{
#if WITH_GAMELIFT
	UE_LOG(DragonCrashDedicatedServer, Log, TEXT("GameLift Server SDK OnStartGameSession"));
	
	if(FString(GameLiftSession.GetName()) == "ffa")
	{
		IsTeamGame = false;
	}

	if (GameLiftSession.GetMaximumPlayerSessionCount() == 2)
	{
		GetWorld()->ServerTravel("DragonCrash2");
	}
	else if (GameLiftSession.GetMaximumPlayerSessionCount() == 4)
	{
		GetWorld()->ServerTravel("DragonCrash4");
	}

	GameLiftSdkModule->ActivateGameSession();
#endif
}

void ADragonCrashGameModeBase::OnTerminate()
{
#if WITH_GAMELIFT
	UE_LOG(DragonCrashDedicatedServer, Log, TEXT("GameLift Server SDK OnTerminate"));
	GameLiftSdkModule->ProcessEnding();
#endif
}

bool ADragonCrashGameModeBase::OnHealthCheck()
{
#if WITH_GAMELIFT
	UE_LOG(DragonCrashDedicatedServer, Log, TEXT("GameLift Server SDK OnHealthCheck"));
	return true;
#else
	return false;
#endif
}

void ADragonCrashGameModeBase::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
#if WITH_GAMELIFT
	FString PlayerSessionId = ParseOption(Options, TEXT("id"));
	UE_LOG(DragonCrashDedicatedServer, Log, TEXT("Player joining with PlayerSessionID") + PlayerSessionId);
	if (!GameLiftSdkModule->AcceptPlayerSession(PlayerSessionId).IsSuccess())
	{
		UE_LOG(DragonCrashDedicatedServer, Log, TEXT("GameLift Server SDK AcceptPlayerSession Failed"));
		ErrorMessage = "failed to validate player session id";
	}
	UE_LOG(DragonCrashDedicatedServer, Log, TEXT("GameLift Server SDK AcceptPlayerSession Success"));
#endif
}

FString ADragonCrashGameModeBase::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
#if WITH_GAMELIFT
	FString PlayerSessionId = ParseOption(Options, TEXT("id"));
	PlayerSessionIds.Add((AController*) NewPlayerController, PlayerSessionId);
#endif
	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

void ADragonCrashGameModeBase::Logout(AController* Exiting)
{
#if WITH_GAMELIFT
	FString* PlayerSessionId = PlayerSessionIds.Find(Exiting);
	if (PlayerSessionId)
	{
		GameLiftSdkModule->RemovePlayerSession(*PlayerSessionId);
	}
#endif
}