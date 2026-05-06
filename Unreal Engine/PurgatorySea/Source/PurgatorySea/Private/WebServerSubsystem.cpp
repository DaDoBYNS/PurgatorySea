// Fill out your copyright notice in the Description page of Project Settings.

#include "WebServerSubsystem.h"

#include "HttpServerModule.h"
#include "IHttpRouter.h"
#include "JsonObjectConverter.h"
#include "PurgatorySeaMultiplayerHandlerInterface.h"
#include "UnrealPosition.h"

void UWebServerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	auto Router = FHttpServerModule::Get().GetHttpRouter(8842);

	Router->BindRoute({"/fireshot"}, EHttpServerRequestVerbs::VERB_OPTIONS, FHttpRequestHandler([](const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete)->bool
	{
		TUniquePtr<FHttpServerResponse> Response = FHttpServerResponse::Ok();

		TArray<FString> AccessControlAllowOrigin;
		AccessControlAllowOrigin.Add(TEXT("*"));
		Response->Headers.Add(TEXT("Access-Control-Allow-Origin"), AccessControlAllowOrigin);

		TArray<FString> AccessControlAllowMethods;
		AccessControlAllowMethods.Add(TEXT("POST, GET, PUT, DELETE, OPTIONS"));
		Response->Headers.Add(TEXT("Access-Control-Allow-Methods"), AccessControlAllowMethods);

		TArray<FString> AccessControlAllowHeaders;
		AccessControlAllowHeaders.Add(TEXT("*"));
		Response->Headers.Add(TEXT("Access-Control-Allow-Headers"), AccessControlAllowHeaders);

		OnComplete(MoveTemp(Response));
		return true;
	}));

	Router->BindRoute({"/fireshot"}, EHttpServerRequestVerbs::VERB_POST, FHttpRequestHandler([this](const FHttpServerRequest& Request, const FHttpResultCallback& OnComplete)->bool
	{
		TSharedPtr<FJsonObject> JsonObject;

		if (!GetJsonObjectFromRequest(Request, JsonObject))
		{
			TUniquePtr<FHttpServerResponse> Response = CreateJsonResponse(
				TEXT("Error"),
				TEXT("InvalidJsonBody"),
				EHttpServerResponseCodes::BadRequest
			);

			OnComplete(MoveTemp(Response));
			return true;
		}

		const TSharedPtr<FJsonObject>* HitPositionObject = nullptr;

		if (!JsonObject->TryGetObjectField(TEXT("HitPosition"), HitPositionObject))
		{
			TUniquePtr<FHttpServerResponse> Response = CreateJsonResponse(
				TEXT("Error"),
				TEXT("MissingHitPosition"),
				EHttpServerResponseCodes::BadRequest
			);

			OnComplete(MoveTemp(Response));
			return true;
		}

		FUnrealPosition UnrealPosition;

		if (!FJsonObjectConverter::JsonObjectToUStruct<FUnrealPosition>((*HitPositionObject).ToSharedRef(), &UnrealPosition))
		{
			TUniquePtr<FHttpServerResponse> Response = CreateJsonResponse(
				TEXT("Error"),
				TEXT("InvalidPosition"),
				EHttpServerResponseCodes::BadRequest
			);

			OnComplete(MoveTemp(Response));
			return true;
		}  

		FString HitStatus = TEXT("NoHandler");

		if (MultiplayerHandler && MultiplayerHandler->GetClass()->ImplementsInterface(UPurgatorySeaMultiplayerHandlerInterface::StaticClass()))
		{
			HitStatus = IPurgatorySeaMultiplayerHandlerInterface::Execute_HandleFireShotRequest(
				MultiplayerHandler,
				UnrealPosition
			);
		}
		
		UE_LOG(LogTemp, Warning, TEXT("POST /fireshot returning HitStatus: %s"), *HitStatus);

		TUniquePtr<FHttpServerResponse> Response = CreateJsonResponse(
			TEXT("HitStatus"),
			HitStatus,
			EHttpServerResponseCodes::Ok
		);

		OnComplete(MoveTemp(Response));
		return true;
	}));

	FHttpServerModule::Get().StartAllListeners();
}

void UWebServerSubsystem::SetMultiplayerHandler(UObject* InHandler)
{
	MultiplayerHandler = InHandler;
}

bool UWebServerSubsystem::GetJsonObjectFromRequest(const FHttpServerRequest& Request, TSharedPtr<FJsonObject>& JsonObject)
{
	if (Request.Body.Num() == 0)
	{
		return false;
	}

	const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(
		BytesToStringFixed(&Request.Body[0], Request.Body.Num())
	);

	FJsonSerializer::Deserialize(JsonReader, JsonObject);

	return JsonObject.IsValid();
}

FString UWebServerSubsystem::BytesToStringFixed(const uint8* Bytes, int32 Length)
{
	FString String = BytesToString(Bytes, Length);

	for (int Index = 0; Index < String.Len(); Index++)
	{
		String[Index] = String[Index] - 1;
	}

	return String;
}

TUniquePtr<FHttpServerResponse> UWebServerSubsystem::CreateJsonResponse(
	const FString& FieldName,
	const FString& FieldValue,
	EHttpServerResponseCodes Code
)
{
	const TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(FieldName, FieldValue);

	FString ResponseBody;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&ResponseBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	TUniquePtr<FHttpServerResponse> Response = FHttpServerResponse::Create(
		ResponseBody,
		TEXT("application/json")
	);

	Response->Code = Code;

	TArray<FString> AccessControlAllowOrigin;
	AccessControlAllowOrigin.Add(TEXT("*"));
	Response->Headers.Add(TEXT("Access-Control-Allow-Origin"), AccessControlAllowOrigin);

	return Response;
}