// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VehicleSpawnPoint.generated.h"

class APawn;
class ATankUnit;
class AVehicleBase;
class AMyAIController;

UCLASS()
class UA2_API AVehicleSpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVehicleSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

        UPROPERTY(EditAnywhere, Category="Team")
        int32 Team;

        // UPROPERTY(EditAnywhere, Category="Spawning")
        // TSubclassOf<APawn> VehicleToSpawn;

        UPROPERTY(EditAnywhere, Category="Spawning")
        TSubclassOf<AVehicleBase> VehicleToSpawn;

        UFUNCTION(BluePrintCallable, Category="Spawn")
        void Spawn();

};
