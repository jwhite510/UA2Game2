// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HostStationAIController.generated.h"

class ATankUnit;
class AHostStation;
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
};
