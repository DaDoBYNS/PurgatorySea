// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpServerConstants.h"
#include "HttpServerRequest.h"
#include "HttpServerResponse.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "WebServerSubsystem.generated.h"
/**
 * 
 */
UCLASS()
class PURGATORYSEA_API UWebServerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	void SetMultiplayerHandler(UObject* InHandler);
	bool GetJsonObjectFromRequest(const FHttpServerRequest& request, TSharedPtr<FJsonObject>& jsonObject);
	FString BytesToStringFixed(const uint8* bytes, int32 length);
	TUniquePtr<FHttpServerResponse> CreateJsonResponse( 
		const FString& FieldName,
		const FString& FieldValue,
		EHttpServerResponseCodes Code
	);
	
	void SendSessionRequest(const FString& OpponentIpAddress);
	
private:
	void OnSessionResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	UPROPERTY()
	TObjectPtr<UObject> MultiplayerHandler = nullptr;
};
