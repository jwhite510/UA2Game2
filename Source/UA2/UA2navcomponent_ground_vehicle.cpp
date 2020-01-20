// Fill out your copyright notice in the Description page of Project Settings.


#include "UA2navcomponent_ground_vehicle.h"
#include "VehicleBase.h"
#include "TankUnit.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

void UUA2navcomponent_ground_vehicle::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{

  // UE_LOG(LogTemp, Warning, TEXT("%s RequestDirectMove called"), *ThisVehicle->GetName());
  FVector ThisVehicleLocation = ThisVehicle->GetActorLocation();

  FVector MoveDirection = MoveVelocity.GetSafeNormal();

  // draw navigation arrow
  DrawDebugLine(
      GetWorld(),
      ThisVehicleLocation,
      ThisVehicleLocation+(MoveDirection*500),
      // 100*(CurrentLocation+ForwardVec),
      FColor(255,255,0), // color
      true, //persitent
      1.,// lifetime
      1,// depth priority
      20 // thickness
      );

  // draw forwardarrow
  UStaticMeshComponent* ThisBaseComponent = Cast<UStaticMeshComponent>(ThisVehicle->GetRootComponent());

  // UE_LOG(LogTemp, Warning, TEXT("ThisBaseComponent name:%s"), *ThisBaseComponent->GetName());

  FVector ForwardVec = ThisBaseComponent->GetForwardVector().GetSafeNormal();
  DrawDebugLine(
      GetWorld(),
      ThisVehicleLocation,
      ThisVehicleLocation+(ForwardVec*300),
      // 100*(CurrentLocation+ForwardVec),
      FColor(255,0,0), // color
      true, //persitent
      1.,// lifetime
      1,// depth priority
      20 // thickness
      );

  FVector CrossProductValue = FVector::CrossProduct(ForwardVec, MoveDirection);
  float DotProductValue = FVector::DotProduct(ForwardVec, MoveDirection);

  // UE_LOG(LogTemp, Warning, TEXT("CrossProductValueZ: %f"), CrossProductValue.Z);
  // DrawDebugLine(
      // GetWorld(),
      // ThisVehicleLocation,
      // ThisVehicleLocation+(DotProductValue*300),
      // // 100*(CurrentLocation+ForwardVec),
      // FColor(255,0,255), // color
      // true, //persitent
      // 1.,// lifetime
      // 1,// depth priority
      // 20 // thickness
      // );

  // UE_LOG(LogTemp, Warning, TEXT("%s DotProductValue:%f"), *ThisVehicle->GetName(), DotProductValue);


  Cast<ATankUnit>(ThisVehicle)->ControlWheels(0.5*DotProductValue, CrossProductValue.Z);



}
void UUA2navcomponent_ground_vehicle::FindActor(AVehicleBase* ThisVehicle)
{
  this->ThisVehicle = ThisVehicle;
}
