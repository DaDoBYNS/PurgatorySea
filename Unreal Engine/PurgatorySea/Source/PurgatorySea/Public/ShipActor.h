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

	virtual void BeginPlay() override;

	void SetVisualState(
		bool bIsSelected,
		bool bIsErrorHighlighted,
		UMaterialInterface* SelectedMaterial,
		UMaterialInterface* ErrorMaterial
	);

private:
	void CacheOriginalMaterials();
	void ApplyMaterialToAllSlots(UMaterialInterface* Material);
	void RestoreOriginalMaterials();

private:
	TMap<UPrimitiveComponent*, TArray<UMaterialInterface*>> OriginalMaterials;

	bool bOriginalMaterialsCached = false;
};