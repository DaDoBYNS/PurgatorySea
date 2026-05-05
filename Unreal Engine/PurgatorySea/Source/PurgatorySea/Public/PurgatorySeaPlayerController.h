// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PurgatorySeaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PURGATORYSEA_API APurgatorySeaPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	void RotateSelectedShip();
};
