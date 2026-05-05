// Fill out your copyright notice in the Description page of Project Settings.


#include "PurgatoryGameModeBase.h"
#include "PurgatorySeaPlayerController.h"

APurgatoryGameModeBase::APurgatoryGameModeBase()
{
	PlayerControllerClass = APurgatorySeaPlayerController::StaticClass();
}
