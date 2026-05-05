// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PURGATORYSEA_API FWebServerSubsystem : public UGameInstanceSubsystem
{
public:
	FWebServerSubsystem();
	~FWebServerSubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
