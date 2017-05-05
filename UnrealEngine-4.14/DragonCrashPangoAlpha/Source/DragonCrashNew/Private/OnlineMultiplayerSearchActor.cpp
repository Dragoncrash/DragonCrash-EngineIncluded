// Fill out your copyright notice in the Description page of Project Settings.

#include "DragonCrashNew.h"
#include "OnlineMultiplayerSearchActor.h"


void AOnlineMultiplayerSearchActor::StartSearch(const FString& MatchmakingURL, const FString& GameType)
{
	FHttpModule* Http = &FHttpModule::Get();

	FString RequestURL(MatchmakingURL);
	RequestURL += "search/";
	RequestURL += GameType;

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &AOnlineMultiplayerSearchActor::OnResponseReceived);
	Request->SetURL(RequestURL);
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

void AOnlineMultiplayerSearchActor::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	if (bWasSuccessful)
	{
		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			if (JsonObject->GetStringField("msg") == "success")
			{
				OnSearchSuccess(JsonObject->GetStringField("id"), JsonObject->GetStringField("ip"), JsonObject->GetStringField("port"));
			}
			else if (JsonObject->GetStringField("msg") == "error")
			{
				OnSearchFailure(JsonObject->GetStringField("error"));
			}
			else
			{
				OnSearchFailure("invalid json response");
			}
		}
		else
		{
			OnSearchFailure("failed to deserialize received response");
		}
	}
	else
	{
		OnSearchFailure("request failed or timed out");
	}
	
	Destroy();
}