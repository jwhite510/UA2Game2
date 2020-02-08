// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStationNavigationAIControl.h"
#include "MovementWaypoint.h"
#include "HostStationNavigationPawn.h"
#include "HostStation.h"



void AHostStationNavigationAIControl::Tick(float DeltaTime)
{

  Super::Tick(DeltaTime);
  // UE_LOG(LogTemp, Warning, TEXT("AHostStationNavigationAIControl tick"));
  // MoveToActor()
  AMovementWaypoint* MovementWaypoint = FindMovementWaypoint();
  if(MovementWaypoint!=nullptr)
  {
    UE_LOG(LogTemp, Warning, TEXT("found MovementWaypoint %s"), *MovementWaypoint->GetActorLocation().ToString());
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
