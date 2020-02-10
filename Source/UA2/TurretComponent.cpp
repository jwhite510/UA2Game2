// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretComponent.h"

// Sets default values for this component's properties
UTurretComponent::UTurretComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTurretComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTurretComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTurretComponent::FireCannon()
{
  FVector ForwardDirection = Barrel->GetUpVector();
  FVector WorldLocation = Barrel->GetComponentLocation();

  AActor* Projectile = GetWorld()->SpawnActor<AActor>(
      ProjectileBluePrint,
      WorldLocation+(-150*ForwardDirection),
      FRotator(0,0,0)
      );

  UStaticMeshComponent* ProjectileMesh = Projectile->FindComponentByClass<UStaticMeshComponent>();


  FVector PawnVelocity = ParentActor->GetVelocity();
  FVector ProjectileVelocity=((-1000*ForwardDirection)+PawnVelocity);
  ProjectileMesh->SetPhysicsLinearVelocity(ProjectileVelocity,true);
}

float UTurretComponent::AimTowards(FVector AimHere)
{
  // UE_LOG(LogTemp, Warning, TEXT("ATankUnit move aim towards %s"), *AimHere.ToString());

  FVector BarrelDirection = TurretBase->GetForwardVector();
  float DotProductValue = FVector::DotProduct(AimHere, BarrelDirection);
  float YawDiff = BarrelDirection.Rotation().Yaw - AimHere.Rotation().Yaw;
  float ElevationDiff = BarrelDirection.Rotation().Pitch - AimHere.Rotation().Pitch;
  // UE_LOG(LogTemp, Warning, TEXT("new new"), YawDiff);

  FRotator CurrentRelativeRotation = TurretBase->GetRelativeRotation();
  if (FMath::Abs(YawDiff) < 180)
  {
    YawDiff = FMath::Clamp<float>(YawDiff, -1, +1);
    CurrentRelativeRotation.Yaw -= 80*YawDiff*GetWorld()->DeltaTimeSeconds;
  }
  else
  {
    YawDiff = FMath::Clamp<float>(YawDiff, -1, +1);
    CurrentRelativeRotation.Yaw += 80*YawDiff*GetWorld()->DeltaTimeSeconds;
  }
  // adjust barrel elevation
  CurrentRelativeRotation.Pitch -= 80*FMath::Clamp<float>(ElevationDiff, -1, +1)*GetWorld()->DeltaTimeSeconds;
  CurrentRelativeRotation.Pitch = FMath::Clamp<float>(CurrentRelativeRotation.Pitch, MinPitch, MaxPitch);
  TurretBase->SetRelativeRotation(CurrentRelativeRotation);

  return DotProductValue;

}
void UTurretComponent::ManualAim(float YValue, float XValue)
{

  // UE_LOG(LogTemp, Warning, TEXT("ManualAim"));
  // UE_LOG(LogTemp, Warning, TEXT("YValue:%f, XValue:%f"), YValue, XValue);
  FVector BarrelDirection = TurretBase->GetForwardVector();
  // UE_LOG(LogTemp, Warning, TEXT("BarrelDirectionBefore:%s"), *BarrelDirection.ToString());

  FRotator BarrelRotation = BarrelDirection.Rotation();
  BarrelRotation.Yaw+=XValue;
  BarrelRotation.Pitch+=YValue;

  BarrelDirection = BarrelRotation.Vector();
  // UE_LOG(LogTemp, Warning, TEXT("BarrelDirectionAfter:%s"), *BarrelDirection.ToString());

  AimTowards(BarrelDirection);

}
