#include "PurgatorySeaBoardPositions.h"

APurgatorySeaBoardPositions::APurgatorySeaBoardPositions()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APurgatorySeaBoardPositions::PlaceShips(const std::vector<std::shared_ptr<FShip>>& CoreShips)
{
	ClearShips();

	FActorSpawnParameters Params;
	FRotator Rot = FRotator::ZeroRotator;

	for (const std::shared_ptr<FShip>& Ship : CoreShips)
	{
		if (!Ship)
			continue;

		FPosition Position = Ship->GetFirstPosition();

		FVector Loc;
		Loc.X = static_cast<int>(Position.Letter) * 100.f;
		Loc.Y = static_cast<int>(Position.Number) * 100.f;
		Loc.Z = 0.f;

		SpawnShip(Ship, Loc, Rot, Params);
	}
}

void APurgatorySeaBoardPositions::ClearShips()
{
	for (AShipActor* Ship : Ships)
	{
		if (Ship)
		{
			Ship->Destroy();
		}
	}

	Ships.Empty();
}

TSubclassOf<AShipActor> APurgatorySeaBoardPositions::GetShipClassByName(const std::string& ShipName) const
{
	if (ShipName == "battleship")
	{
		return BattleshipClass;
	}

	if (ShipName == "aircraft carrier")
	{
		return AircraftCarrierClass;
	}

	return nullptr;
}

void APurgatorySeaBoardPositions::SpawnShip(
	const std::shared_ptr<FShip>& Ship,
	FVector Loc,
	FRotator Rot,
	FActorSpawnParameters Params
)
{
	if (!Ship)
		return;

	TSubclassOf<AShipActor> ShipClass = GetShipClassByName(Ship->GetName());

	if (ShipClass == nullptr)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("No Unreal class assigned for ship name: %s"),
			*FString(Ship->GetName().c_str())
		);

		return;
	}

	AShipActor* ShipObj = GetWorld()->SpawnActor<AShipActor>(
		ShipClass,
		Loc,
		Rot,
		Params
	);

	if (!ShipObj)
		return;

	ShipObj->SetSelectedVisual(Ship->GetIsSelected(), SelectedShipMaterial);

	Ships.Add(ShipObj);
}