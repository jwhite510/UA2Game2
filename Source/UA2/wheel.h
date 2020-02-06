// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "wheel.generated.h"

UCLASS()
class UA2_API Awheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Awheel();


        UFUNCTION(BluePrintCallable, Category="Drive")
        void DriveWheel(float DriveSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

        UFUNCTION(BluePrintCallable, Category="Setup")
        void FindComponents(UStaticMeshComponent* Wheel, UStaticMeshComponent* Cube);

        UStaticMeshComponent* Wheel = nullptr;
        UStaticMeshComponent* Cube = nullptr;

        float TorqueScalar = 1.0;

        float DriveDirection = 0;

        void GetRotationSpeed(float DeltaTime);

        float RotationSpeed = 0;
  private:
        FVector RotationVectorOld;
        FVector RotationVectorNew;
        float SpeedScalar;


};
