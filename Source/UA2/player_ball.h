// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "player_ball.generated.h"

class UMovement;

UCLASS()
class UA2_API Aplayer_ball : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Aplayer_ball();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

        UStaticMeshComponent* Body;
        UStaticMeshComponent* Wheel_LF;
        UStaticMeshComponent* Wheel_2;
        UStaticMeshComponent* Wheel_3;
        UStaticMeshComponent* Wheel_4;

        UFUNCTION(BluePrintCallable, Category="Input")
        void MoveForward(float Value);

        UFUNCTION(BluePrintCallable, Category="Setup")
        void GetComponents(UStaticMeshComponent* Body, UStaticMeshComponent* Wheel_LF, UStaticMeshComponent* Wheel_2, UStaticMeshComponent* Wheel_3, UStaticMeshComponent* Wheel_4);

        UPROPERTY(EditDefaultsOnly, Category="Movement")
        float ForceMovement = 9999;

        float Direction = 0;
        float wheel_pitch = 0;


};
