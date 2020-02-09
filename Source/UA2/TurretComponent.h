// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TurretComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UA2_API UTurretComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTurretComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
        UStaticMeshComponent* TurretBase = nullptr;
        UStaticMeshComponent* Barrel = nullptr;

        void FireCannon();

        float AimTowards(FVector AimHere);

        float MinPitch = -10;
        float MaxPitch = 10;

        TSubclassOf<AActor> ProjectileBluePrint;

        AActor* ParentActor;
};
