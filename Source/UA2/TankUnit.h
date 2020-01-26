// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleBase.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Containers/Array.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "TankUnit.generated.h"

class AActor;
class AMyAIController;
class Awheel;
class UMoveToLocationMarker;
/**
 * 
 */
UCLASS()
class UA2_API ATankUnit : public AVehicleBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ATankUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

        UFUNCTION(BluePrintCallable, Category="Control")
        void ControlWheels(float ForwardValue, float RightValue);

        UFUNCTION(BluePrintCallable, Category="Print")
        void PrintActors(TArray<AActor*> ActorArray);

        UFUNCTION(BluePrintCallable, Category="Possession")
        void PossessPawn(int32 PawnNumber);

        UPROPERTY(EditDefaultsOnly, Category="Spawning")
        TSubclassOf<ATankUnit> MovingVehicle_BP;

        UFUNCTION(BluePrintCallable, Category="Debug")
        void SwitchPawn();

        void AimTowards(FVector AimHere);

        UStaticMeshComponent* TurretBase = nullptr;
        UStaticMeshComponent* Barrel = nullptr;

        Awheel* FrontRightWheel = nullptr;
        Awheel* FrontLeftWheel = nullptr;
        Awheel* BackRightWheel = nullptr;
        Awheel* BackLeftWheel = nullptr;

        UFUNCTION(BluePrintCallable, Category="Setup")
        void FindComponents(UStaticMeshComponent* TurretBase, UStaticMeshComponent* Barrel, Awheel* FrontRightWheel, Awheel* FrontLeftWheel, Awheel* BackRightWheel, Awheel* BackLeftWheel);

        UFUNCTION(BluePrintCallable, Category="Input")
        void HandleLeftMouseClick();

        UPROPERTY(EditDefaultsOnly, Category="Setup")
        TSubclassOf<AActor> ProjectileBluePrint;


        AMyAIController* ThisAIController=nullptr;

        UFUNCTION(BluePrintCallable, Category="Possession")
        void Reposess();

        // move to location component
        UMoveToLocationMarker* MoveToLocationComponent;
};
