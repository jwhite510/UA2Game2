// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "MyAIController.generated.h"

class ATankUnit;
class AVehicleBase;

/**
 * 
 */
UCLASS()
class UA2_API AMyAIController : public AAIController
{
	GENERATED_BODY()

        private:
        virtual void Tick(float DeltaTime) override;

        float LastFireTime=0;
        ATankUnit * ControllerPawn;

        public:
        AActor* FindNearestTarget();

        void MoveToWayPoint();

        void AimAndFire(AActor* Target);





	
};
