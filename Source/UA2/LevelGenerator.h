// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "LevelGenerator.generated.h"

/**
 * 
 */
UCLASS()
class UA2_API ALevelGenerator : public ALevelScriptActor
{
	GENERATED_BODY()

        protected:
	virtual void BeginPlay() override;

        int LevelGridSize = 10;
	
};
