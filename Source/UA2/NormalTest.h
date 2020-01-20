// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NormalTest.generated.h"

UCLASS()
class UA2_API ANormalTest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANormalTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


        UFUNCTION(BluePrintCallable, Category="Setup")
        void GetComponents(UStaticMeshComponent* Cube);

        UStaticMeshComponent* Cube=nullptr;

};
