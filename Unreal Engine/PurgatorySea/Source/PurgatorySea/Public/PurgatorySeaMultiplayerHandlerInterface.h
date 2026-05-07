#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UnrealPosition.h"
#include "PurgatorySeaMultiplayerHandlerInterface.generated.h"

UINTERFACE(BlueprintType)
class PURGATORYSEA_API UPurgatorySeaMultiplayerHandlerInterface : public UInterface
{
	GENERATED_BODY()
};

class PURGATORYSEA_API IPurgatorySeaMultiplayerHandlerInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString HandleFireShotRequest(FUnrealPosition Position);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString HandleSessionRequest();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString HandleSessionAccepted();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool HandleReadyRequest();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HandleOpponentReadyAccepted();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FString HandleForfeitRequest();
};