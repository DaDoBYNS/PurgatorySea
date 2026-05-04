#include "PurgatorySeaBoardPositions.h"

APurgatorySeaBoardPositions::APurgatorySeaBoardPositions()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APurgatorySeaBoardPositions::PlaceShips(const std::vector<std::shared_ptr<FShip>>& CoreShips)
{
	ClearShips();

	FVector Loc;
	FRotator Rot = FRotator::ZeroRotator;
	FActorSpawnParameters Params;

	for (const std::shared_ptr<FShip>& Ship : CoreShips)
	{
		if (!Ship)
			continue;

		if (Ship->GetDimension() != 4)
			continue;

		FPosition Position = Ship->GetFirstPosition();

		Loc.X = static_cast<int>(Position.Letter) * 100.f;
		Loc.Y = static_cast<int>(Position.Number) * 100.f;
		Loc.Z = 0.f;

		SpawnBattleship(Ship, Loc, Rot, Params);
	}
}

void APurgatorySeaBoardPositions::SpawnBattleship(
	const std::shared_ptr<FShip>& Ship,
	FVector Loc,
	FRotator Rot,
	FActorSpawnParameters Params
)
{
	if (!Ship)
		return;

	if (BattleshipClass == nullptr)
		return;

	AShipActor* ShipObj = GetWorld()->SpawnActor<AShipActor>(
		BattleshipClass,
		Loc,
		Rot,
		Params
	);

	if (!ShipObj)
		return;

	if (Ship->GetIsSelected())
	{
		ShipObj->SetSelectedVisual(true, SelectedShipMaterial);
	}
	else
	{
		ShipObj->SetSelectedVisual(false, nullptr);
	}

	Ships.Add(ShipObj);
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