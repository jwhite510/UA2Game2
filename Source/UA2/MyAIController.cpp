// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawDebugHelpers.h"
#include "MyAIController.h"
#include "TankUnit.h"

void AMyAIController::Tick(float DeltaTime)
{

  Super::Tick(DeltaTime);

  // aim at player
  ATankUnit *ControllerPawn = Cast<ATankUnit>( GetPawn() );
  if (ControllerPawn != nullptr)
  {

    // find target
    AActor* TargetActor = FindTarget(ControllerPawn);


    if(TargetActor!=nullptr)
    {

      FVector TargetLocation = TargetActor->GetActorLocation();
      FVector ThisPawnLocation = ControllerPawn->GetActorLocation();
      FVector AimDirection = TargetLocation - ThisPawnLocation;

      // DrawDebugLine(
      //     GetWorld(),
      //     ThisPawnLocation,
      //     ThisPawnLocation + (100*AimDirection.GetSafeNormal()),
      //     FColor(0,0,255), // color
      //     true, //persitent
      //     1.,// lifetime
      //     1,// depth priority
      //     20 // thickness
      //     );


      // UE_LOG(LogTemp, Warning, TEXT("AimTowards called"));

      // check if the actors are far away
      float Distance = FVector::Dist(TargetLocation, ThisPawnLocation);

      if(Distance > 1000)
      {
        // move toward target
        MoveToActor(TargetActor, 100);
      }
      else
      {
        // dont move
        ControllerPawn->ControlWheels(0.0, 0.0);

      }

      ControllerPawn->AimTowards(AimDirection);



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
