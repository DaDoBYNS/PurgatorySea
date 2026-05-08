#include "ShipActor.h"

#include "Components/PrimitiveComponent.h"

AShipActor::AShipActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AShipActor::BeginPlay()
{
	Super::BeginPlay();

	CacheOriginalMaterials();
}

void AShipActor::CacheOriginalMaterials()
{
	if (bOriginalMaterialsCached)
	{
		return;
	}

	OriginalMaterials.Empty();

	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetComponents<UPrimitiveComponent>(PrimitiveComponents);

	for (UPrimitiveComponent* PrimitiveComponent : PrimitiveComponents)
	{
		if (!PrimitiveComponent)
		{
			continue;
		}

		TArray<UMaterialInterface*> Materials;

		const int MaterialCount = PrimitiveComponent->GetNumMaterials();

		for (int i = 0; i < MaterialCount; i++)
		{
			Materials.Add(PrimitiveComponent->GetMaterial(i));
		}

		OriginalMaterials.Add(PrimitiveComponent, Materials);
	}

	bOriginalMaterialsCached = true;
}

void AShipActor::ApplyMaterialToAllSlots(UMaterialInterface* Material)
{
	if (!Material)
	{
		return;
	}

	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetComponents<UPrimitiveComponent>(PrimitiveComponents);

	for (UPrimitiveComponent* PrimitiveComponent : PrimitiveComponents)
	{
		if (!PrimitiveComponent)
		{
			continue;
		}

		const int MaterialCount = PrimitiveComponent->GetNumMaterials();

		for (int i = 0; i < MaterialCount; i++)
		{
			PrimitiveComponent->SetMaterial(i, Material);
		}
	}
}

void AShipActor::RestoreOriginalMaterials()
{
	CacheOriginalMaterials();

	for (const TPair<UPrimitiveComponent*, TArray<UMaterialInterface*>>& Pair : OriginalMaterials)
	{
		UPrimitiveComponent* PrimitiveComponent = Pair.Key;

		if (!PrimitiveComponent)
		{
			continue;
		}

		const TArray<UMaterialInterface*>& Materials = Pair.Value;

		for (int i = 0; i < Materials.Num(); i++)
		{
			PrimitiveComponent->SetMaterial(i, Materials[i]);
		}
	}
}

void AShipActor::SetVisualState(
	bool bIsSelected,
	bool bIsErrorHighlighted,
	UMaterialInterface* SelectedMaterial,
	UMaterialInterface* ErrorMaterial
)
{
	CacheOriginalMaterials();

	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetComponents<UPrimitiveComponent>(PrimitiveComponents);

	for (UPrimitiveComponent* PrimitiveComponent : PrimitiveComponents)
	{
		if (!PrimitiveComponent)
		{
			continue;
		}

		PrimitiveComponent->SetCollisionResponseToChannel(
			ECC_Visibility,
			bIsSelected ? ECR_Ignore : ECR_Block
		);
	}

	if (bIsErrorHighlighted && ErrorMaterial)
	{
		ApplyMaterialToAllSlots(ErrorMaterial);
		return;
	}

	if (bIsSelected && SelectedMaterial)
	{
		ApplyMaterialToAllSlots(SelectedMaterial);
		return;
	}

	RestoreOriginalMaterials();
}