// Fill out your copyright notice in the Description page of Project Settings.


#include "PurgatorySeaControllerActor.h"

#include "WebServerSubsystem.h"

#include "PurgatorySeaWidget.h"
#include "Engine/Engine.h"

#include "Validation.h"
#include "WebClientSubsystem.h"

APurgatorySeaControllerActor::APurgatorySeaControllerActor()
	: bHasSession(false)
	, bIsLocalReady(false)
	, bIsOpponentReady(false)
	, bHasMatchStarted(false)
	, bHasMatchEnded(false)
	, bHasLocalPlayerWon(false)
	, bHasLocalPlayerLost(false)
{
	PrimaryActorTick.bCanEverTick = true;
}

void APurgatorySeaControllerActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UWebServerSubsystem* WebServerSubsystem = GameInstance->GetSubsystem<UWebServerSubsystem>())
		{
			WebServerSubsystem->SetMultiplayerHandler(this);
		}

		if (UWebClientSubsystem* WebClientSubsystem = GameInstance->GetSubsystem<UWebClientSubsystem>())
		{
			WebClientSubsystem->SetMultiplayerHandler(this);
		}
	}
	
	GameController = std::make_shared<FGameController>(); 

	std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
	std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();

	GameController->SetBoard(Board);
	GameController->SetSelection(Selection);

	Selection->SetBoard(Board);

	GameController->InitGame();
	
	if (GEngine && GEngine->GameViewport)
	{
		SAssignNew(PurgatorySeaWidget, SPurgatorySeaWidget)
		.ControllerActor(this);

		GEngine->GameViewport->AddViewportWidgetContent(PurgatorySeaWidget.ToSharedRef());
	}
	
	BoardPositions->PlaceShips(GameController->GetBoard()->GetShips());
}

// Called every frame
void APurgatorySeaControllerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APurgatorySeaControllerActor::SelectShip(int Letter, int Number)
{
	if (!GameController)
		return;

	FPosition Position{
		static_cast<ELetter>(Letter),
		static_cast<ENumber>(Number)
	};

	GameController->SelectShipAt(Position);
	
	BoardPositions->PlaceShips(GameController->GetBoard()->GetShips());
}

void APurgatorySeaControllerActor::MoveSelectedShip(int Letter, int Number)
{
	if (!GameController)
		return;

	FPosition Position{
		static_cast<ELetter>(Letter),
		static_cast<ENumber>(Number)
	};

	GameController->MoveShipTo(Position);
	
	BoardPositions->PlaceShips(GameController->GetBoard()->GetShips());
}

void APurgatorySeaControllerActor::InitGame()
{
	if (!GameController)
		return;

	GameController->InitGame();
}

void APurgatorySeaControllerActor::OnShipClicked(AActor* HitActor)
{
	if (!GameController || !HitActor)
		return;

	FPosition Position{
		static_cast<ELetter>(FMath::RoundToInt(HitActor->GetActorLocation().X / 100.f)),
		static_cast<ENumber>(FMath::RoundToInt(HitActor->GetActorLocation().Y / 100.f))
	};

	std::shared_ptr<FShip> Ship = GameController->SelectShipAt(Position);

	if (!Ship)
		return;

	UE_LOG(LogTemp, Warning, TEXT("Selected ship name: %s"), *FString(Ship->GetName().c_str()));
	
	BoardPositions->PlaceShips(GameController->GetBoard()->GetShips());
}

void APurgatorySeaControllerActor::OnTileClicked(AActor* HitActor)
{
	if (!GameController || !HitActor) return;
	if (GameController->GetSelection()->GetSelectedShip() == nullptr) return; 
	
	FPosition Position{
		static_cast<int>(HitActor->GetActorLocation().X / 100.f),
		static_cast<int>(HitActor->GetActorLocation().Y / 100.f)
	};

	GameController->MoveShipTo(Position);
	auto SelectedShip = GameController->GetSelection()->GetSelectedShip(); 
	std::vector<FPosition> Positions = SelectedShip->GetPositions();
	FString PositionsText;

	for (const FPosition& ShipPosition : Positions)
	{
		PositionsText += FString::Printf(
			TEXT("[Letter = %d, Number = %d] "),
			ShipPosition.Letter,
			ShipPosition.Number
		);
	}

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Positions of %s : %s"),
		*FString(SelectedShip->GetName().c_str()),
		*PositionsText
	);
	
	BoardPositions->PlaceShips(GameController->GetBoard()->GetShips());
}

void APurgatorySeaControllerActor::EmptySelectedShip()
{
	if (!GameController) return; 
	if (GameController->GetSelection()->GetSelectedShip() == nullptr) return; 
	
	GameController->EmptySelectedShip();
	
	BoardPositions->PlaceShips(GameController->GetBoard()->GetShips());
}

void APurgatorySeaControllerActor::RotateSelectedShip()
{
	if (!GameController)
	{
		return;
	}

	if (GameController->GetSelection()->GetSelectedShip() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No selected ship to rotate"));
		return;
	}

	GameController->RotateSelectedShip();
	
	BoardPositions->PlaceShips(GameController->GetBoard()->GetShips());
}

void APurgatorySeaControllerActor::RequestSession(const FString& InOpponentIpAddress, const FString& LocalIpAddress)
{
	if (InOpponentIpAddress.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot request session. Opponent IP is empty."));
		return;
	}

	if (LocalIpAddress.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot request session. Local IP is empty."));
		return;
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UWebClientSubsystem* WebClientSubsystem = GetGameInstance()->GetSubsystem<UWebClientSubsystem>();

		if (WebClientSubsystem)
		{
			WebClientSubsystem->SendSessionRequest(InOpponentIpAddress, LocalIpAddress);
		}
	}
}

FString APurgatorySeaControllerActor::CreateLocalSession(const FString& InOpponentIpAddress)
{
	if (InOpponentIpAddress.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create session. Opponent IP is empty."));
		return TEXT("Denied");
	}

	if (bHasSession)
	{
		UE_LOG(LogTemp, Warning, TEXT("Session already created."));
		return TEXT("Created");
	}

	OpponentIpAddress = InOpponentIpAddress;
	bHasSession = true;

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("Local session created. Opponent IP saved: %s"),
		*OpponentIpAddress
	);

	return TEXT("Created");
}

FString APurgatorySeaControllerActor::HandleSessionRequest_Implementation(const FString& RequesterIpAddress)
{
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("HandleSessionRequest called. Requester IP: %s"),
		*RequesterIpAddress
	);

	return CreateLocalSession(RequesterIpAddress);
}

FString APurgatorySeaControllerActor::HandleSessionAccepted_Implementation(const FString& InOpponentIpAddress)
{
	UE_LOG(
		LogTemp,
		Warning,
		TEXT("HandleSessionAccepted called. Opponent IP: %s"),
		*InOpponentIpAddress
	);

	return CreateLocalSession(InOpponentIpAddress);
}

FString APurgatorySeaControllerActor::ConvertHitStatusToString(EHitStatus HitStatus) const
{
	switch (HitStatus)
	{
	case EHitStatus::Miss:
		return TEXT("Miss");

	case EHitStatus::Hit:
		return TEXT("Hit");

	case EHitStatus::Sink:
		return TEXT("Sink");

	case EHitStatus::AlredyShot:
		return TEXT("AlreadyShot");

	default:
		return TEXT("Error");
	}
}

FString APurgatorySeaControllerActor::HandleFireShotRequest_Implementation(FUnrealPosition Position)
{
	if (!GameController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot handle fire shot. Missing GameController."));
		return TEXT("Error");
	}

	if (bHasMatchEnded)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot handle fire shot. Match already ended."));
		return TEXT("GameOver");
	}

	FPosition CorePosition{
		static_cast<ELetter>(Position.Letter),
		static_cast<ENumber>(Position.Number)
	};

	EHitStatus ShotResult = GameController->ReceiveShot(CorePosition);

	if (ShotResult == EHitStatus::AlredyShot)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("FireShot received at Letter: %d, Number: %d. Result: AlreadyShot"),
			Position.Letter,
			Position.Number
		);

		return TEXT("AlreadyShot");
	}

	if (GameController->HasLost())
	{
		bHasMatchEnded = true;
		bHasLocalPlayerLost = true;
		bHasLocalPlayerWon = false;

		UE_LOG(
			LogTemp,
			Warning,
			TEXT("FireShot received at Letter: %d, Number: %d. Local player lost. Returning GameOver."),
			Position.Letter,
			Position.Number
		);

		return TEXT("GameOver");
	}

	FString ShotResultText = ConvertHitStatusToString(ShotResult);

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("FireShot received at Letter: %d, Number: %d. Result: %s"),
		Position.Letter,
		Position.Number,
		*ShotResultText
	);

	return ShotResultText;
}

void APurgatorySeaControllerActor::RequestReady()
{
	if (OpponentIpAddress.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot ready. Opponent IP is empty."));
		return;
	}
	
	if (bHasMatchStarted)
	{
		UE_LOG(LogTemp, Warning, TEXT("Match already started. Cannot send ready again."));
		return;
	}

	if (!bHasSession)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot ready. No session created yet."));
		return;
	}

	if (!ValidateLocalShips())
	{
		UE_LOG(LogTemp, Warning, TEXT("Ships validation failed. Ready request will not be sent."));
		return;
	}

	bIsLocalReady = true;

	UE_LOG(LogTemp, Warning, TEXT("Ships validation passed. Local player is ready. Sending ready request to opponent."));

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UWebClientSubsystem* WebClientSubsystem = GameInstance->GetSubsystem<UWebClientSubsystem>();

		if (WebClientSubsystem)
		{
			WebClientSubsystem->SendReadyRequest(OpponentIpAddress);
		}
	}

	TryStartMatch();
}

bool APurgatorySeaControllerActor::ValidateLocalShips()
{
	if (!GameController || !GameController->GetBoard())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot validate ships. Missing GameController or Board."));
		return false;
	}

	FValidation Validation;
	Validation.SetBoard(GameController->GetBoard());
	Validation.ValidateShips();

	bool bIsValid = Validation.GetIsValid();

	BoardPositions->PlaceShips(GameController->GetBoard()->GetShips());

	UE_LOG(LogTemp, Warning, TEXT("Local ships validation result: %s"), bIsValid ? TEXT("Valid") : TEXT("Invalid"));

	return bIsValid;
}

void APurgatorySeaControllerActor::RequestForfeit()
{
	if (OpponentIpAddress.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot forfeit. Opponent IP is empty."));
		return;
	}
	
	if (bHasMatchEnded)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot forfeit. Match already ended."));
		return;
	}

	if (!bHasSession)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot forfeit. No session created yet."));
		return;
	}

	bHasMatchEnded = true;
	bHasLocalPlayerLost = true;
	bHasLocalPlayerWon = false;

	UE_LOG(LogTemp, Warning, TEXT("Local player forfeited. Local player lost. Opponent won."));

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UWebClientSubsystem* WebClientSubsystem = GetGameInstance()->GetSubsystem<UWebClientSubsystem>();

		if (WebClientSubsystem)
		{
			WebClientSubsystem->SendForfeitRequest(OpponentIpAddress);
		}
	}
}

bool APurgatorySeaControllerActor::TryStartMatch()
{
	if (bHasMatchStarted)
	{
		return true;
	}

	if (!bIsLocalReady || !bIsOpponentReady)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Match cannot start yet. LocalReady: %s, OpponentReady: %s"),
			bIsLocalReady ? TEXT("true") : TEXT("false"),
			bIsOpponentReady ? TEXT("true") : TEXT("false")
		);

		return false;
	}

	bHasMatchStarted = true;

	UE_LOG(LogTemp, Warning, TEXT("Both players are ready. Match can start."));

	return true;
}

void APurgatorySeaControllerActor::HandleOpponentReadyAccepted_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleOpponentReadyAccepted called."));

	bIsOpponentReady = true;

	TryStartMatch();
}

FString APurgatorySeaControllerActor::HandleForfeitRequest_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleForfeitRequest called. Opponent forfeited."));

	if (bHasMatchEnded)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot accept forfeit. Match already ended."));
		return TEXT("Denied");
	}

	if (!bHasSession)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot accept forfeit. No session created yet."));
		return TEXT("Denied");
	}

	bHasMatchEnded = true;
	bHasLocalPlayerWon = true;
	bHasLocalPlayerLost = false;

	UE_LOG(LogTemp, Warning, TEXT("Opponent forfeited. Local player won."));

	return TEXT("Won");
}

void APurgatorySeaControllerActor::HandleFireShotResponse_Implementation(FUnrealPosition Position, const FString& HitStatus)
{
	if (!GameController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot handle fire shot response. Missing GameController."));
		return;
	}

	FPosition CorePosition{
		static_cast<ELetter>(Position.Letter),
		static_cast<ENumber>(Position.Number)
	};

	if (HitStatus == TEXT("Miss"))
	{
		GameController->RegisterEnemyBoardShot(CorePosition, EHitStatus::Miss);

		UE_LOG(LogTemp, Warning, TEXT("FireShot response handled. Result: Miss."));
		return;
	}

	if (HitStatus == TEXT("Hit"))
	{
		GameController->RegisterEnemyBoardShot(CorePosition, EHitStatus::Hit);

		UE_LOG(LogTemp, Warning, TEXT("FireShot response handled. Result: Hit."));
		return;
	}

	if (HitStatus == TEXT("Sink"))
	{
		GameController->RegisterEnemyBoardShot(CorePosition, EHitStatus::Sink);

		UE_LOG(LogTemp, Warning, TEXT("FireShot response handled. Result: Sink."));
		return;
	}

	if (HitStatus == TEXT("AlreadyShot"))
	{
		UE_LOG(LogTemp, Warning, TEXT("FireShot response handled. Result: AlreadyShot."));
		return;
	}

	if (HitStatus == TEXT("GameOver"))
	{
		GameController->RegisterEnemyBoardShot(CorePosition, EHitStatus::Sink);

		bHasMatchEnded = true;
		bHasLocalPlayerWon = true;
		bHasLocalPlayerLost = false;

		UE_LOG(LogTemp, Warning, TEXT("FireShot response handled. Opponent lost. Local player won."));
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Unknown FireShot response: %s"), *HitStatus);
}

bool APurgatorySeaControllerActor::HandleReadyRequest_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleReadyRequest called. Opponent is ready."));

	bIsOpponentReady = true;

	TryStartMatch();

	return bIsLocalReady;
}

void APurgatorySeaControllerActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GEngine && GEngine->GameViewport && PurgatorySeaWidget.IsValid())
	{
		GEngine->GameViewport->RemoveViewportWidgetContent(PurgatorySeaWidget.ToSharedRef());
		PurgatorySeaWidget.Reset();
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UWebServerSubsystem* WebServerSubsystem = GameInstance->GetSubsystem<UWebServerSubsystem>();
		
		if (WebServerSubsystem)
		{
			WebServerSubsystem->SetMultiplayerHandler(nullptr);
		}

		UWebClientSubsystem* WebClientSubsystem = GameInstance->GetSubsystem<UWebClientSubsystem>();

		if (WebClientSubsystem)
		{
			WebClientSubsystem->SetMultiplayerHandler(nullptr);
		}
	}
	
	Super::EndPlay(EndPlayReason);
}
