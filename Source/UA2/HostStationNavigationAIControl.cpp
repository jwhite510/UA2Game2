// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStationNavigationAIControl.h"
#include "MovementWaypoint.h"
#include "HostStationNavigationPawn.h"
#include "HostStation.h"
#include "TankUnit.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "TurretComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "DrawDebugHelpers.h"
#include "VehicleBase.h"



void AHostStationNavigationAIControl::Tick(float DeltaTime)
{

  Super::Tick(DeltaTime);
  // UE_LOG(LogTemp, Warning, TEXT("AHostStationNavigationAIControl Tick running"));
  AMovementWaypoint* MovementWaypoint = FindMovementWaypoint();
  // move to waypoint
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

  // aim at target
  AVehicleBase* _ControllerPawn = Cast<AVehicleBase>(Cast<AHostStationNavigationPawn>(GetPawn())->ParentHostStation);


  // find target
  TArray<AActor*> ActorsWithTag;
  UGameplayStatics::GetAllActorsWithTag(
      GetWorld(),
      FName("vehicletag"),
      ActorsWithTag
      );


  // target the nearest actor
  AActor* TargetActor = nullptr;
  float ClosestDistance = 10000;
  for(auto& _Actor : ActorsWithTag){
    if ( _Actor != _ControllerPawn )
    {
      AVehicleBase* FoundActorVehicle = Cast<AVehicleBase>(_Actor);
      // get distance
      FVector TargetActorLocation = FoundActorVehicle->GetActorLocation();
      FVector ThisActorLocation = _ControllerPawn->GetActorLocation();
      float Distance = FVector::Dist(TargetActorLocation, ThisActorLocation);
      // check if this is the closest and not on the same team
      if (Distance < ClosestDistance && FoundActorVehicle->GetTeam()!=_ControllerPawn->GetTeam())
      {
        TargetActor = FoundActorVehicle;
        ClosestDistance = Distance;
      }
    }
  }
  // aim towards the actor
  if(TargetActor!=nullptr)
  {
    FVector OutLaunchVelocity(0);
    FVector StartLocation=Cast<AHostStationNavigationPawn>(GetPawn())->ParentHostStation->TurretComponent->Barrel->GetComponentLocation();
    StartLocation+=(Cast<AHostStationNavigationPawn>(GetPawn())->ParentHostStation->TurretComponent->Barrel->GetUpVector())*(-150);

    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
        this,
        OutLaunchVelocity,
        StartLocation,
        TargetActor->GetActorLocation(),
        10000,
        false,
        0,
        0,
        ESuggestProjVelocityTraceOption::DoNotTrace // parameter must be present to prevent bug
        );

    float DotProd = 0;
    if(bHaveAimSolution)
    {
      DotProd = Cast<AHostStationNavigationPawn>(GetPawn())->ParentHostStation->TurretComponent->AimTowards(OutLaunchVelocity.GetSafeNormal());
    }

    float TimeNow = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
    if(TimeNow > (LastFireTime+3) && bHaveAimSolution && (DotProd>0.8))
    {
      Cast<AHostStationNavigationPawn>(GetPawn())->ParentHostStation->TurretComponent->FireCannon();
      LastFireTime = TimeNow;
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
