#include "WebClientSubsystem.h"

#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "PurgatorySeaMultiplayerHandlerInterface.h"

void UWebClientSubsystem::SetMultiplayerHandler(UObject* InHandler)
{
	MultiplayerHandler = InHandler;
}

void UWebClientSubsystem::SendSessionRequest(const FString& OpponentIpAddress, const FString& LocalIpAddress)
{
	PendingSessionOpponentIpAddress = OpponentIpAddress;

	FString Url = FString::Printf(
		TEXT("http://%s:8842/session"),
		*OpponentIpAddress
	);

	const TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(TEXT("RequesterIpAddress"), LocalIpAddress);

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetContentAsString(RequestBody);

	Request->OnProcessRequestComplete().BindUObject(
		this,
		&UWebClientSubsystem::OnSessionResponseReceived
	);

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Sending POST /session to: %s with LocalIpAddress: %s"),
		*Url,
		*LocalIpAddress
	);

	Request->ProcessRequest();
}

void UWebClientSubsystem::SendReadyRequest(const FString& OpponentIpAddress)
{
	FString Url = FString::Printf(
		TEXT("http://%s:8842/ready"),
		*OpponentIpAddress
	);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("GET"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->OnProcessRequestComplete().BindUObject(
		this,
		&UWebClientSubsystem::OnReadyResponseReceived
	);

	UE_LOG(LogTemp, Warning, TEXT("Sending GET /ready to: %s"), *Url);

	Request->ProcessRequest();
}

void UWebClientSubsystem::SendFireShotRequest(const FString& OpponentIpAddress, const FUnrealPosition& HitPosition)
{
	PendingFireShotPosition = HitPosition;
	bHasPendingFireShotPosition = true;
	
	FString Url = FString::Printf(
		TEXT("http://%s:8842/fireshot"),
		*OpponentIpAddress
	);

	const TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();

	TSharedPtr<FJsonObject> HitPositionObject = FJsonObjectConverter::UStructToJsonObject(HitPosition);
	JsonObject->SetObjectField(TEXT("HitPosition"), HitPositionObject);

	FString RequestBody;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetContentAsString(RequestBody);

	Request->OnProcessRequestComplete().BindUObject(
		this,
		&UWebClientSubsystem::OnFireShotResponseReceived
	);

	UE_LOG(LogTemp, Warning, TEXT("Sending POST /fireshot to: %s body: %s"), *Url, *RequestBody);

	Request->ProcessRequest();
}

void UWebClientSubsystem::SendForfeitRequest(const FString& OpponentIpAddress)
{
	FString Url = FString::Printf(
		TEXT("http://%s:8842/forfeit"),
		*OpponentIpAddress
	);

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

	Request->SetURL(Url);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->OnProcessRequestComplete().BindUObject(
		this,
		&UWebClientSubsystem::OnForfeitResponseReceived
	);

	UE_LOG(LogTemp, Warning, TEXT("Sending POST /forfeit to: %s"), *Url);

	Request->ProcessRequest();
}

void UWebClientSubsystem::OnSessionResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Session request failed. No valid response."));
		return;
	}

	FString ResponseBody = Response->GetContentAsString();

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Session response code: %d body: %s"),
		Response->GetResponseCode(),
		*ResponseBody
	);

	if (Response->GetResponseCode() != 200)
	{
		return;
	}

	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid session response json."));
		return;
	}

	FString SessionStatus;

	if (!JsonObject->TryGetStringField(TEXT("SessionStatus"), SessionStatus))
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing SessionStatus field."));
		return;
	}

	if (SessionStatus != TEXT("Created"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Session was not created by opponent."));
		return;
	}

	if (MultiplayerHandler && MultiplayerHandler->GetClass()->ImplementsInterface(UPurgatorySeaMultiplayerHandlerInterface::StaticClass()))
	{
		IPurgatorySeaMultiplayerHandlerInterface::Execute_HandleSessionAccepted(
			MultiplayerHandler,
			PendingSessionOpponentIpAddress
		);
	}
}

void UWebClientSubsystem::OnReadyResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Ready request failed. No valid response."));
		return;
	}

	FString ResponseBody = Response->GetContentAsString();

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Ready response code: %d body: %s"),
		Response->GetResponseCode(),
		*ResponseBody
	);

	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid ready response json."));
		return;
	}

	bool bOpponentIsReady = false;

	if (!JsonObject->TryGetBoolField(TEXT("bIsReady"), bOpponentIsReady))
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing bIsReady field."));
		return;
	}

	if (!bOpponentIsReady)
	{
		UE_LOG(LogTemp, Warning, TEXT("Opponent is not ready yet."));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Opponent is already ready."));

	if (MultiplayerHandler && MultiplayerHandler->GetClass()->ImplementsInterface(UPurgatorySeaMultiplayerHandlerInterface::StaticClass()))
	{
		IPurgatorySeaMultiplayerHandlerInterface::Execute_HandleOpponentReadyAccepted(
			MultiplayerHandler
		);
	}
}

void UWebClientSubsystem::OnFireShotResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("FireShot request failed. No valid response."));
		return;
	}

	FString ResponseBody = Response->GetContentAsString();

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("FireShot response code: %d body: %s"),
		Response->GetResponseCode(),
		*ResponseBody
	);

	if (Response->GetResponseCode() != 200)
	{
		UE_LOG(LogTemp, Warning, TEXT("FireShot denied by opponent."));
		return;
	}

	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid fireshot response json."));
		return;
	}

	FString HitStatus;

	if (!JsonObject->TryGetStringField(TEXT("HitStatus"), HitStatus))
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing HitStatus field."));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("FireShot result: %s"), *HitStatus); 
	
	if (!bHasPendingFireShotPosition)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot handle fire shot response. Missing pending fire shot position."));
		return;
	}

	if (MultiplayerHandler && MultiplayerHandler->GetClass()->ImplementsInterface(UPurgatorySeaMultiplayerHandlerInterface::StaticClass()))
	{
		IPurgatorySeaMultiplayerHandlerInterface::Execute_HandleFireShotResponse(
			MultiplayerHandler,
			PendingFireShotPosition,
			HitStatus
		);
	}

	bHasPendingFireShotPosition = false;
}

void UWebClientSubsystem::OnForfeitResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Forfeit request failed. No valid response."));
		return;
	}

	FString ResponseBody = Response->GetContentAsString();

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Forfeit response code: %d body: %s"),
		Response->GetResponseCode(),
		*ResponseBody
	);

	if (Response->GetResponseCode() != 200)
	{
		UE_LOG(LogTemp, Warning, TEXT("Forfeit denied by opponent."));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Forfeit accepted. Local player lost.")); 
}