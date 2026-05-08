#pragma once

#include <memory>
#include <string>
#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipActor.h"

#include <Ship.h>

#include "PurgatorySeaBoardPositions.generated.h"

UCLASS()
class PURGATORYSEA_API APurgatorySeaBoardPositions : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<AShipActor*> Ships;

public:
	APurgatorySeaBoardPositions();

	UPROPERTY(EditAnywhere, Category = "Ships")
	TSubclassOf<AShipActor> BattleshipClass;

	UPROPERTY(EditAnywhere, Category = "Ships")
	TSubclassOf<AShipActor> AircraftCarrierClass;
	
	UPROPERTY(EditAnywhere, Category = "Ships")
	TSubclassOf<AShipActor> SubmarineClass;
	
	UPROPERTY(EditAnywhere, Category = "Ships")
	TSubclassOf<AShipActor> TorpedoClass;
	
	UPROPERTY(EditAnywhere, Category = "Ships")
	TSubclassOf<AShipActor> SwiftBoatClass;

	UPROPERTY(EditAnywhere, Category = "Ships")
	UMaterialInterface* SelectedShipMaterial;

	void PlaceShips(const std::vector<std::shared_ptr<FShip>>& CoreShips);
	void ClearShips();

private:
	void SpawnShip(
		const std::shared_ptr<FShip>& Ship,
		FVector Loc,
		FRotator Rot,
		FActorSpawnParameters Params
	);

	TSubclassOf<AShipActor> GetShipClassByName(const std::string& ShipName) const;
};