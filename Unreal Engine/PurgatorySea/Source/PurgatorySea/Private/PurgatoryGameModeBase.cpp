// Fill out your copyright notice in the Description page of Project Settings.


#include "PurgatoryGameModeBase.h"
#include "PurgatorySeaPlayerController.h"
#include "WebServerSubsystem.h"

APurgatoryGameModeBase::APurgatoryGameModeBase()
{
	PlayerControllerClass = APurgatorySeaPlayerController::StaticClass();
	
//	GetGameInstance()->GetSubsystem<UWebServerSubsystem>()
}
