// Fill out your copyright notice in the Description page of Project Settings.


#include "PurgatorySeaControllerActor.h"


// Sets default values
APurgatorySeaControllerActor::APurgatorySeaControllerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APurgatorySeaControllerActor::BeginPlay()
{
	Super::BeginPlay();

	GameController = std::make_shared<FGameController>();

	std::shared_ptr<FBoard> Board = std::make_shared<FBoard>();
	std::shared_ptr<FSelection> Selection = std::make_shared<FSelection>();

	GameController->SetBoard(Board);
	GameController->SetSelection(Selection);

	Selection->SetBoard(Board);

	GameController->InitGame();
	
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
			static_cast<int>(ShipPosition.Letter),
			static_cast<int>(ShipPosition.Number)
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
