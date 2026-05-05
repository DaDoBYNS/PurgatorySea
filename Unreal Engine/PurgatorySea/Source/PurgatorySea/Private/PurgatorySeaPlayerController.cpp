#include "PurgatorySeaPlayerController.h"

#include "PurgatorySeaControllerActor.h"
#include "EngineUtils.h"

void APurgatorySeaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
}

void APurgatorySeaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindKey(EKeys::R, IE_Pressed, this, &APurgatorySeaPlayerController::RotateSelectedShip);
}

void APurgatorySeaPlayerController::RotateSelectedShip()
{
	for (TActorIterator<APurgatorySeaControllerActor> It(GetWorld()); It; ++It)
	{
		APurgatorySeaControllerActor* ControllerActor = *It;

		if (ControllerActor == nullptr)
		{
			continue;
		}

		ControllerActor->RotateSelectedShip();
		return;
	}
}
