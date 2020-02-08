// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "HostStationNavMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class UA2_API UHostStationNavMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
        virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
};
