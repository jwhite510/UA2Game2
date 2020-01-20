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
        AActor* FindTarget(ATankUnit *_ControllerPawn);

        public:





	
};
