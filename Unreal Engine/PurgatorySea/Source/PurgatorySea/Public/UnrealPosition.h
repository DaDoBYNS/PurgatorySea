// UnrealPosition.h
#pragma once

#include "CoreMinimal.h"
#include "UnrealPosition.generated.h"

USTRUCT(BlueprintType)
struct FUnrealPosition
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int32 Letter = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 Number = 0;
};