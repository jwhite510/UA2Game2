// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleBase.h"
#include "Kismet/GameplayStatics.h"
#include "HostStation.generated.h"

class ATankUnit;
class UMoveToLocationMarker;
class UArrowComponent;

UCLASS()
class UA2_API AHostStation : public AVehicleBase
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHostStation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


        UFUNCTION(BluePrintCallable, Category="Input")
        void HandleLeftMouseClick();

        UFUNCTION(BluePrintImplementableEvent, Category="UI Mode")
        void ComponentSpawnThing();

        bool SpawnState=0;

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HostStation")
        int32 HostStationEnergy=0;

        float EnergyIncrementTime = 1.4; // seconds

        float LastIncrementTime=0;

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HostStation")
        int32 OwnedTiles;

        UChildActorComponent* HostSChildNavigationPawn;

        UMoveToLocationMarker* MoveToLocationComponent;

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="HostStation")
        UArrowComponent* ArrowToGround;

        float TargetFloatingHeight = 1000;

        void MoveToTargetHeight(FVector GroundLocation);


};
