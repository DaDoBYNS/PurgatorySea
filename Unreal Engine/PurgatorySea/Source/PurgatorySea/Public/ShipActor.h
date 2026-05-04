#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipActor.generated.h"

UCLASS()
class PURGATORYSEA_API AShipActor : public AActor
{
	GENERATED_BODY()

public:
	AShipActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void SetSelectedVisual(bool bIsSelected, UMaterialInterface* SelectedMaterial);
};