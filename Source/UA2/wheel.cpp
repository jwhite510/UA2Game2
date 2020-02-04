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

        Wheel->AddTorqueInRadians(DriveDirection*ForwardVec*TorqueScalar, FName("None"), 1);

        // rotation speed
        FRotator WheelRotation = Wheel->GetRelativeRotation();

        // get rotation speed
        FVector RotationVectorNew = WheelRotation.Vector();
        FVector Distance = RotationVectorNew - RotationVectorOld;
        SpeedScalar = Distance.Size()*DeltaTime;
        RotationVectorOld = RotationVectorNew;
        // UE_LOG(LogTemp, Warning, TEXT("SpeedScalar:%f"), SpeedScalar);


        DrawDebugLine(
            GetWorld(),
            GetActorLocation(),
            GetActorLocation()+WheelRotation.Vector()*100,
            FColor(255,0,255), // color
            true, //persitent
            1.,// lifetime
            1,// depth priority
            20 // thickness
            );
        // distance
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

void Awheel::ApplyBrakes()
{

  UE_LOG(LogTemp, Warning, TEXT("%s Awheel:: APPLY BRAKES for real 999"), *GetName());

  FVector ForwardVec = Cube->GetRightVector().GetSafeNormal();
  Wheel->AddTorqueInRadians(SpeedScalar*ForwardVec*(-10000), FName("None"), 1);
  UE_LOG(LogTemp, Warning, TEXT("SetRelativeRotation"));
  // Wheel->SetRelativeRotation(FRotator(0,0,0));

}
