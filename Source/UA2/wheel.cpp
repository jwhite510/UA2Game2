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


        // set point
        float SetPoint = 10*DriveDirection;
        SpeedScalar;

        UE_LOG(LogTemp, Warning, TEXT("wheel:%s"), *GetName());
        // UE_LOG(LogTemp, Warning, TEXT("DriveDirection:%f"), DriveDirection);
        UE_LOG(LogTemp, Warning, TEXT("SpeedScalar:%f"), SpeedScalar);
        UE_LOG(LogTemp, Warning, TEXT("SetPoint:%f"), SetPoint);
        float ApplyTorque = (SetPoint-SpeedScalar)*DeltaTime;
        UE_LOG(LogTemp, Warning, TEXT("Apply:%f"), ApplyTorque);

        FVector ForwardVec = Cube->GetRightVector().GetSafeNormal();

        Wheel->AddTorqueInRadians(ApplyTorque*ForwardVec*TorqueScalar, FName("None"), 1);

        // sets the SpeedScalar float to be used in controls
        GetRotationSpeed(DeltaTime);



        // UE_LOG(LogTemp, Warning, TEXT("%s SpeedScalar:%f"), *GetParentActor()->GetName(), SpeedScalar);



}

void Awheel::DriveWheel(float DriveSpeed)
{

  // UE_LOG(LogTemp, Warning, TEXT("DriveWheel: %f"), DriveSpeed);
  DriveDirection = DriveSpeed;

}

void Awheel::FindComponents(UStaticMeshComponent* WheelIn, UStaticMeshComponent* CubeIn)
{
  // UE_LOG(LogTemp, Warning, TEXT("FindComponents called"));
  this->Wheel = WheelIn;
  this->Cube = CubeIn;
}

void Awheel::ApplyBrakes()
{

  UE_LOG(LogTemp, Warning, TEXT("%s Awheel:: APPLY BRAKES for real 999"), *GetName());

  FVector ForwardVec = Cube->GetRightVector().GetSafeNormal();
  Wheel->AddTorqueInRadians((-1)*SpeedScalar*ForwardVec*(10), FName("None"), 1);
  // UE_LOG(LogTemp, Warning, TEXT("SetRelativeRotation"));
  // Wheel->SetRelativeRotation(FRotator(0,0,0));

}
void Awheel::GetRotationSpeed(float DeltaTime)
{

  // get wheel rotation speed

  // rotation speed
  FRotator WheelRotation = Wheel->GetRelativeRotation();

  // get rotation speed
  RotationVectorNew = WheelRotation.Vector();


  // find the angle between vectors
  float DotProductValue = FVector::DotProduct(RotationVectorNew, RotationVectorOld);
  DotProductValue *= (1/RotationVectorNew.Size());
  DotProductValue *= (1/RotationVectorOld.Size());
  float DAngle = FMath::Acos(DotProductValue);
  DAngle/=DeltaTime;

  // cross product
  FVector CrossProductValue = FVector::CrossProduct(RotationVectorNew, RotationVectorOld);
  CrossProductValue = CrossProductValue.GetSafeNormal();


  DotProductValue = FVector::DotProduct(Wheel->GetRightVector(),CrossProductValue);
  // UE_LOG(LogTemp, Warning, TEXT("%s DotProductValue:%f"), *GetParentActor()->GetName(), DotProductValue);
  SpeedScalar = (-1)*DotProductValue*DAngle;

  RotationVectorOld = RotationVectorNew;

  // DrawDebugLine(
      // GetWorld(),
      // GetActorLocation(),
      // GetActorLocation()+Wheel->GetRightVector()*10,
      // FColor(0,255,0), // color
      // true, //persitent
      // 1.,// lifetime
      // 1,// depth priority
      // 20 // thickness
      // );

  // DrawDebugLine(
      // GetWorld(),
      // GetActorLocation(),
      // GetActorLocation()+CrossProductValue*(10)*DAngle,
      // FColor(0,0,255), // color
      // true, //persitent
      // 1.,// lifetime
      // 1,// depth priority
      // 20 // thickness
      // );

  // DrawDebugLine(
      // GetWorld(),
      // GetActorLocation(),
      // GetActorLocation()+WheelRotation.Vector()*100,
      // FColor(255,0,255), // color
      // true, //persitent
      // 1.,// lifetime
      // 1,// depth priority
      // 20 // thickness
      // );

}
