// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FloatingVehicleWidgetC.generated.h"

/**
 * 
 */
UCLASS()
class UA2_API UFloatingVehicleWidgetC : public UUserWidget
{
	GENERATED_BODY()

  public:
        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Something")
        float HealthBarPercent = 1.0;
	
};
