// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStationNavMovementComponent.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "HostStation.h"
#include "HostStationNavigationPawn.h"


void UHostStationNavMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
  if(Parent!=nullptr)
  {
    // get parent host station
    AHostStation* ThisHostStation = Cast<AHostStationNavigationPawn>(Parent)->ParentHostStation;
    if(ThisHostStation!=nullptr)
    {

      FVector MoveDirection = ThisHostStation->GetActorLocation();
      FVector _MoveVelocity = MoveVelocity;
      _MoveVelocity.Z = 0;
      MoveDirection+=(5.5*_MoveVelocity.GetSafeNormal());
      ThisHostStation->SetActorLocation(MoveDirection);


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
  }

}
void UHostStationNavMovementComponent::FindParent(AActor* ParentIn)
{
  Parent = ParentIn;
}
