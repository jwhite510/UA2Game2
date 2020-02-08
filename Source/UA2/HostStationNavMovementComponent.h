// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "HostStationNavMovementComponent.generated.h"

/**
 * 
 */
class AActor;

UCLASS()
class UA2_API UHostStationNavMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
        virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

  public:
        void FindParent(AActor *ParentIn);
        AActor* Parent;
};
