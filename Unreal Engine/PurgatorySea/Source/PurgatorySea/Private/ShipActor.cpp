#include "ShipActor.h"
#include "Components/PrimitiveComponent.h"

AShipActor::AShipActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShipActor::BeginPlay()
{
	Super::BeginPlay();
}

void AShipActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShipActor::SetSelectedVisual(bool bIsSelected, UMaterialInterface* SelectedMaterial)
{
	TArray<UPrimitiveComponent*> PrimitiveComponents;
	GetComponents<UPrimitiveComponent>(PrimitiveComponents);

	for (UPrimitiveComponent* PrimitiveComponent : PrimitiveComponents)
	{
		if (!PrimitiveComponent)
			continue;

		if (bIsSelected)
		{
			PrimitiveComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

			if (SelectedMaterial)
			{
				int MaterialCount = PrimitiveComponent->GetNumMaterials();

				for (int i = 0; i < MaterialCount; i++)
				{
					PrimitiveComponent->SetMaterial(i, SelectedMaterial);
				}
			}
		}
		else
		{
			PrimitiveComponent->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		}
	}
}