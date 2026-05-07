#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "UnrealPosition.h"
#include "WebClientSubsystem.generated.h"

UCLASS()
class PURGATORYSEA_API UWebClientSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void SetMultiplayerHandler(UObject* InHandler);

	void SendSessionRequest(const FString& OpponentIpAddress, const FString& LocalIpAddress);
	void SendReadyRequest(const FString& OpponentIpAddress);
	void SendFireShotRequest(const FString& OpponentIpAddress, const FUnrealPosition& HitPosition);
	void SendForfeitRequest(const FString& OpponentIpAddress);

private:
	void OnSessionResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnReadyResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnFireShotResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void OnForfeitResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

private:
	UPROPERTY()
	TObjectPtr<UObject> MultiplayerHandler = nullptr;

	FString PendingSessionOpponentIpAddress;
};