// Fill out your copyright notice in the Description page of Project Settings.


#include "wheel.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
Awheel::Awheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Awheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Awheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

        FVector CurrentLocation = GetActorLocation();

        // FVector ForwardVec = Wheel->GetForwardVector();

        FVector ForwardVec = Cube->GetRightVector().GetSafeNormal();

        // UE_LOG(LogTemp, Warning, TEXT("drive forwared"));

        // DrawDebugLine(
        //     GetWorld(),
        //     CurrentLocation,
        //     CurrentLocation+ForwardVec*(-100),
        //     // 100*(CurrentLocation+ForwardVec),
        //     FColor(0,255,0),
        //     true,
        //     1.,
        //     1,
        //     10
        //     );

        // ForwardVec = ForwardVec * DeltaTime;
        // UE_LOG(LogTemp, Warning, TEXT("calling drive: %f"), DriveDirection);
        Wheel->AddTorqueInRadians(DriveDirection*ForwardVec*TorqueScalar, FName("None"), 1);
}

void Awheel::DriveWheel(float DriveSpeed)
{

  // UE_LOG(LogTemp, Warning, TEXT("DriveWheel: %f"), DriveSpeed);
  DriveDirection = DriveSpeed;

}

void Awheel::FindComponents(UStaticMeshComponent* Wheel, UStaticMeshComponent* Cube)
{
  // UE_LOG(LogTemp, Warning, TEXT("FindComponents called"));
  this->Wheel = Wheel;
  this->Cube = Cube;
}

