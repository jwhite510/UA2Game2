// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStationNavigationAIControl.h"
#include "MovementWaypoint.h"
#include "HostStationNavigationPawn.h"
#include "HostStation.h"
#include "TankUnit.h"
#include "Navigation/PathFollowingComponent.h"



void AHostStationNavigationAIControl::Tick(float DeltaTime)
{

  Super::Tick(DeltaTime);
  // UE_LOG(LogTemp, Warning, TEXT("AHostStationNavigationAIControl Tick running"));
  AMovementWaypoint* MovementWaypoint = FindMovementWaypoint();
  if(MovementWaypoint!=nullptr)
  {
    // UE_LOG(LogTemp, Warning, TEXT("found MovementWaypoint %s"), *MovementWaypoint->GetActorLocation().ToString());
    float Distance = FVector::Dist(GetPawn()->GetActorLocation(), MovementWaypoint->GetActorLocation());
    if (Distance>10.0)
    {
      MoveToActor(MovementWaypoint, 10);
    }
    else
    {
      StopMovement();
    }
  }
}

AMovementWaypoint* AHostStationNavigationAIControl::FindMovementWaypoint()
{
    TArray<AActor*> ChildActors;

    // TODO change this
    Cast<AHostStationNavigationPawn>(GetPawn())->ParentHostStation->GetAllChildActors(ChildActors);

    for(auto& _Actor : ChildActors){
      // check if actor is of type waypoint
      AMovementWaypoint* ChildMovementWaypoint = Cast<AMovementWaypoint>(_Actor);
      if(ChildMovementWaypoint!=nullptr)
      {
        return ChildMovementWaypoint;
      }
    }
    return nullptr;
}
