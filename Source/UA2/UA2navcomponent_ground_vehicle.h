// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "UA2navcomponent_ground_vehicle.generated.h"

class AVehicleBase;

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UA2_API UUA2navcomponent_ground_vehicle : public UNavMovementComponent
{
	GENERATED_BODY()
	
        virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


        UFUNCTION(BlueprintCallable, Category="Input")
        void FindActor(AVehicleBase* ThisVehicle);

        AVehicleBase* ThisVehicle = nullptr;
};
