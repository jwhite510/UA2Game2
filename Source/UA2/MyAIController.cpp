// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawDebugHelpers.h"
#include "MyAIController.h"
#include "TankUnit.h"
#include "MovementWaypoint.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void AMyAIController::Tick(float DeltaTime)
{

  Super::Tick(DeltaTime);

  // aim at player
  ATankUnit *ControllerPawn = Cast<ATankUnit>( GetPawn() );
  if (ControllerPawn != nullptr)
  {

    // find target
    AActor* TargetActor = FindTarget(ControllerPawn);

    // try to find waypoint
    TArray<AActor*> ChidActors;
    GetPawn()->GetAllChildActors(ChidActors);
    // UE_LOG(LogTemp, Warning, TEXT("Child Actors of %s"), *ControllerPawn->GetName());
    bool FoundWaypoint = 0;
    for(auto& _Actor : ChidActors){
      // UE_LOG(LogTemp, Warning, TEXT("ChildActorName:%s"), *_Actor->GetName());
      // check if actor is of type waypoint
      AMovementWaypoint* ChildMovementWaypoint = Cast<AMovementWaypoint>(_Actor);
      if(ChildMovementWaypoint!=nullptr)
      {

        // if distance is less than something
        float DistanceToWaypoint = FVector::Dist(GetPawn()->GetActorLocation(), ChildMovementWaypoint->GetActorLocation());
        // UE_LOG(LogTemp, Warning, TEXT("DistanceToWaypoint:%f"), DistanceToWaypoint);

        // apply brakes
        if(DistanceToWaypoint<300)
        {
          ControllerPawn->ControlWheels(0.0, 0.0);
          FoundWaypoint = 1;
          break;
        }
        MoveToActor(ChildMovementWaypoint, 10000);
        FoundWaypoint = 1;
        break;
      }
    }
    if(!FoundWaypoint)
    {
      StopMovement();
      // dont move wheels
      ControllerPawn->ControlWheels(0.0, 0.0);
    }

    // target and move toward this actor
    if(TargetActor!=nullptr)
    {
      FVector TargetLocation = TargetActor->GetActorLocation();
      FVector ThisPawnLocation = ControllerPawn->GetActorLocation();
      FVector AimDirection = TargetLocation - ThisPawnLocation;

      FVector OutLaunchVelocity(0);
      FVector StartLocation=Cast<ATankUnit>(GetPawn())->Barrel->GetComponentLocation();
      StartLocation+=(Cast<ATankUnit>(GetPawn())->Barrel->GetUpVector())*(-150);
      bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
          this,
          OutLaunchVelocity,
          StartLocation,
          TargetLocation,
          1000,
          false,
          0,
          0,
          ESuggestProjVelocityTraceOption::DoNotTrace // parameter must be present to prevent bug
          );
      // UE_LOG(LogTemp, Warning, TEXT("bHaveAimSolution:%i"), bHaveAimSolution);

      // check if the actors are far away
      float Distance = FVector::Dist(TargetLocation, ThisPawnLocation);

      if(Distance > 1000)
      {
        // move toward target
        // MoveToActor(TargetActor, 100);
      }
      else
      {
        // dont move
        // ControllerPawn->ControlWheels(0.0, 0.0);
      }

      float DotProd = 0;
      if(bHaveAimSolution)
      {
        DotProd = ControllerPawn->AimTowards(OutLaunchVelocity.GetSafeNormal());
      }
      else
      {
        ControllerPawn->AimTowards(AimDirection);
      }

      float TimeNow = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
      if(TimeNow > (LastFireTime+3) && bHaveAimSolution && (DotProd>0.8))
      {
        // ControllerPawn->FireCannon();
        LastFireTime = TimeNow;
        // UE_LOG(LogTemp, Warning, TEXT("firing, dot:%f"), DotProd);
      }
    }

  }


}

AActor* AMyAIController::FindTarget(ATankUnit *_ControllerPawn)
{

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
    return TargetActor;
}
