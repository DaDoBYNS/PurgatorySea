// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <memory>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameController.h" 
#include "PurgatorySeaBoardPositions.h"
#include "PurgatorySeaMultiplayerHandlerInterface.h"
#include "PurgatorySeaControllerActor.generated.h"

UCLASS()
class PURGATORYSEA_API APurgatorySeaControllerActor : public AActor, public IPurgatorySeaMultiplayerHandlerInterface
{
	GENERATED_BODY()

	std::shared_ptr<FGameController> GameController; 
	TSet<FString> ReceivedShots;
	FString MakeShotKey(int32 Letter, int32 Number) const;
public:
	// Sets default values for this actor's properties
	APurgatorySeaControllerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void SelectShip(int Letter, int Number);

	UFUNCTION(BlueprintCallable)
	void MoveSelectedShip(int Letter, int Number);
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Purgatory Sea")
	APurgatorySeaBoardPositions* BoardPositions;
	
	UFUNCTION(BlueprintCallable)
	void InitGame();
	
	UFUNCTION(BlueprintCallable)
	void OnShipClicked(AActor* HitActor);

	UFUNCTION(BlueprintCallable)
	void OnTileClicked(AActor* HitActor);
	
	UFUNCTION(BlueprintCallable)
	void EmptySelectedShip();
	
	UFUNCTION(BlueprintCallable)
	void RotateSelectedShip();
	
	virtual FString HandleFireShotRequest_Implementation(FUnrealPosition Position) override;

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
