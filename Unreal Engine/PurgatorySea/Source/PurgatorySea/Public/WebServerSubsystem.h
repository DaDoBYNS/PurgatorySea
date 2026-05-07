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

private:
	bool GetJsonObjectFromRequest(const FHttpServerRequest& Request, TSharedPtr<FJsonObject>& JsonObject);
	FString BytesToStringFixed(const uint8* Bytes, int32 Length);

	TUniquePtr<FHttpServerResponse> CreateJsonResponse(
		const FString& FieldName,
		const FString& FieldValue,
		EHttpServerResponseCodes Code
	);

	TUniquePtr<FHttpServerResponse> CreateJsonBoolResponse(
		const FString& FieldName,
		bool bFieldValue,
		EHttpServerResponseCodes Code
	);

private:
	UPROPERTY()
	TObjectPtr<UObject> MultiplayerHandler = nullptr;
};