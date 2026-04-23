// Fill out your copyright notice in the Description page of Project Settings.


#include "PurgatoryGameModeBase.h"

APurgatoryGameModeBase::APurgatoryGameModeBase()
{
	Board = std::make_shared<FBoard>();
	Board->SetInitTest(true); 
	
	if (Board->GetInitTest())
	{
		UE_LOG(LogTemp, Warning, TEXT("funziona"));  
	}
}
