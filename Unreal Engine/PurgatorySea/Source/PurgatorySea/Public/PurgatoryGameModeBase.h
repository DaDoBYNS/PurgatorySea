// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <memory>

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Board.h"

#include "PurgatoryGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PURGATORYSEA_API APurgatoryGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	std::shared_ptr<FBoard> Board;
	
public: 
	APurgatoryGameModeBase(); 
	
};
