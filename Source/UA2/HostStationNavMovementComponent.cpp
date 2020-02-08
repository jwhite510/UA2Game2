// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStationNavMovementComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"


void UHostStationNavMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
  UE_LOG(LogTemp, Warning, TEXT("UHostStationNavMovementComponent RequestDirectMove called"));
  UE_LOG(LogTemp, Warning, TEXT("im being called!!!!"));
  DrawDebugLine(
      GetWorld(),
      Parent->GetActorLocation(),
      Parent->GetActorLocation()+(100*MoveVelocity.GetSafeNormal()),
      FColor(255,0,0), // color
      true, //persitent
      1.,// lifetime
      1,// depth priority
      60 // thickness
      );

}
void UHostStationNavMovementComponent::FindParent(AActor *ParentIn)
{
  Parent = ParentIn;
}
