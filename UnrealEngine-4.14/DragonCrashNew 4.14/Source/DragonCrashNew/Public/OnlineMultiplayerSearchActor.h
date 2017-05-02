// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Online/HTTP/Public/Http.h"

#include "GameFramework/Actor.h"
#include "OnlineMultiplayerSearchActor.generated.h"

UCLASS()
class DRAGONCRASHNEW_API AOnlineMultiplayerSearchActor : public AActor
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintCallable, Category = "Search")
	void StartSearch(const FString& MatchmakingURL, const FString& GameType);

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnSearchSuccess"))
	void OnSearchSuccess(const FString& PlayerSessionId, const FString& ServerIp, const FString& ServerPort);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnSearchFailure"))
	void OnSearchFailure(const FString& Error);
};
