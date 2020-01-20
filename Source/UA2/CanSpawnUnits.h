// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CanSpawnUnits.generated.h"

class ATankUnit;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UA2_API UCanSpawnUnits : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCanSpawnUnits();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

        UFUNCTION(BluePrintCallable, Category="Debug")
        void SpawnThingAtLocation();

        UPROPERTY(EditDefaultsOnly, Category="Spawning")
        TSubclassOf<ATankUnit> TankUnitBP;
		
};
