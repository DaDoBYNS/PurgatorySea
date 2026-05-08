// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <memory>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameController.h" 
#include "PurgatorySeaBoardPositions.h"
#include "PurgatorySeaMultiplayerHandlerInterface.h"
#include "Camera/CameraActor.h"
#include "PurgatorySeaControllerActor.generated.h"

UCLASS()
class PURGATORYSEA_API APurgatorySeaControllerActor : 
    public AActor, 
    public IPurgatorySeaMultiplayerHandlerInterface
{
    GENERATED_BODY()

    std::shared_ptr<FGameController> GameController; 
    TSet<FString> ReceivedShots;
    bool bHasSession;
    bool bIsLocalReady;
    bool bIsOpponentReady;
    bool bHasMatchStarted;
    
    UPROPERTY()
    bool bHasMatchEnded;

    UPROPERTY()
    bool bHasLocalPlayerWon;

    UPROPERTY()
    bool bHasLocalPlayerLost;
    
    TSharedPtr<class SPurgatorySeaWidget> PurgatorySeaWidget;
    
    FString CreateLocalSession(const FString& InOpponentIpAddress);

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
    
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Purgatory Sea")
    ACameraActor* CameraHorizontal;
    
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Purgatory Sea")
    ACameraActor* CameraVertical;
    
    UPROPERTY(EditAnywhere, Category="Board")
    UMaterialInterface* VerticalMaterial;

    UPROPERTY(EditAnywhere, Category="Board")
    UMaterialInterface* HorizontalMaterial;
    
    UFUNCTION(BlueprintCallable)
    void InitGame();
    
    UFUNCTION(BlueprintCallable)
    void OnShipClicked(AActor* HitActor);
    
    UFUNCTION(BlueprintCallable)
    void OnEnemyTileClicked(AActor* HitActor);

    UFUNCTION(BlueprintCallable)
    void OnTileClicked(AActor* HitActor);
    
    UFUNCTION(BlueprintCallable)
    void EmptySelectedShip();
    
    UFUNCTION(BlueprintCallable)
    void RotateSelectedShip();
    
    UFUNCTION(BlueprintCallable)
    void RequestSession(const FString& InOpponentIpAddress, const FString& LocalIpAddress);

    virtual FString HandleSessionRequest_Implementation(const FString& RequesterIpAddress) override;

    virtual FString HandleSessionAccepted_Implementation(const FString& InOpponentIpAddress) override;
    FString ConvertHitStatusToString(EHitStatus HitStatus) const;

    virtual FString HandleFireShotRequest_Implementation(FUnrealPosition Position) override;
    
    UPROPERTY(BlueprintReadOnly)
    FString OpponentIpAddress;
    
    UFUNCTION(BlueprintCallable)
    void RequestReady(); 

    UFUNCTION(BlueprintCallable)
    bool ValidateLocalShips();
    
    UFUNCTION(BlueprintCallable)
    void RequestForfeit();

    bool TryStartMatch();
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy Board")
    TSubclassOf<AActor> EnemyShotPinActorClass;

    UPROPERTY()
    TMap<FIntPoint, AActor*> EnemyShotPins;

    void SpawnEnemyShotPin(FUnrealPosition Position, FVector TileLocation);

    void SetEnemyShotPinResult(FUnrealPosition Position, bool bIsHit);

    virtual bool HandleReadyRequest_Implementation() override; 
    virtual void HandleOpponentReadyAccepted_Implementation() override;
    virtual FString HandleForfeitRequest_Implementation() override;
    virtual void HandleFireShotResponse_Implementation(FUnrealPosition Position, const FString& HitStatus) override;
    
    void UpdateBoardMaterials(bool bUseVertical);
    bool bIsUsingVerticalCamera;
protected:
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
 