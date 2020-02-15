// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HostStationAIController.generated.h"

class ATankUnit;
class AHostStation;


UENUM()
enum VehicleStatus
{
  Idle UMETA(DisplayName = "Idle"),
  Stopped UMETA(DisplayName = "Stopped"),
  Moving UMETA(DisplayName = "Moving"),
  Attacking UMETA(DisplayName = "Attacking"),
  Capturing UMETA(DisplayName = "Capturing")
};


/**
 * 
 */
UCLASS()
class UA2_API AHostStationAIController : public AAIController
{
	GENERATED_BODY()

  public:
        virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

        int32 ThisTeam;

        TArray<ATankUnit*> GetTankUnitsOnThisTeam();

        AHostStation* ThisHostStation;

        void SpawnTank();

        TMap<ATankUnit*, VehicleStatus> VehicleStatusTMap;

        void OrderVehicleAttackNearestEnemy(ATankUnit* TankUnit);

        void CaptureNearestTile(ATankUnit* TankUnit);
};
