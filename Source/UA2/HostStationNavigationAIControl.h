// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HostStationNavigationAIControl.generated.h"

class AMovementWaypoint;

/**
 * 
 */
UCLASS()
class UA2_API AHostStationNavigationAIControl : public AAIController
{
	GENERATED_BODY()

        virtual void Tick(float DeltaTime) override;

        AMovementWaypoint* FindMovementWaypoint();


        float LastFireTime=0;




	
};
