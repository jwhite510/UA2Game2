// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStationAIController.h"
#include "HostStation.h"
#include "TankUnit.h"
#include "DrawDebugHelpers.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CanSpawnUnits.h"
#include "MyAIController.h"
#include "MoveToLocationMarker.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CapturableGridPoint.h"

void AHostStationAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  // UE_LOG(LogTemp, Warning, TEXT("AHostStationAIController:"));
  ThisHostStation = Cast<AHostStation>(GetPawn());
  if(ThisHostStation!=nullptr)
  {
    ThisTeam = ThisHostStation->GetTeam();
    // UE_LOG(LogTemp, Warning, TEXT("ThisTeam:%i"), ThisTeam);
    if(ThisTeam == 1)
    {
      // destroy this controller beause this host station belongs to the player
      Destroy();
      return;
    }

    // UE_LOG(LogTemp, Warning, TEXT("remove actors from other team"));
    // tmap units
    TArray<ATankUnit*> TanksOnThisTeam = GetTankUnitsOnThisTeam();
    for(auto& _Actor : TanksOnThisTeam)
    {
      if(!VehicleStatusTMap.Contains(_Actor))
      {
        VehicleStatusTMap.Add(_Actor, VehicleStatus::Idle);
      }
    }

    if(GetPawn()!=nullptr)
    {
      // print this host station name
      // UE_LOG(LogTemp, Warning, TEXT("ThisHostStation: %s"), *GetPawn()->GetName());
    }

    for(auto& Elem : VehicleStatusTMap)
    {
      if(Elem.Key!=nullptr && !Elem.Key->IsActorBeingDestroyed()) // if the tank has not been destroyed
      {

        Elem.Key; // the ATankUnit that needs to be given a command
        Elem.Value; // the enum
        // if the current status of the vehicle is idle
        if(Elem.Value == VehicleStatus::Idle)
        {
          Elem.Value = VehicleStatus::Capturing;
        }
        else if(Elem.Value == VehicleStatus::Attacking)
        {
          // UE_LOG(LogTemp, Warning, TEXT("Attacking called"));
          OrderVehicleAttackNearestEnemy(Elem.Key);
        }
        else if(Elem.Value == VehicleStatus::Capturing)
        {
          UE_LOG(LogTemp, Warning, TEXT("%s Capturing called"), *Elem.Key->GetName());
          CaptureNearestTile(Elem.Key);
        }
      }

    }



    // spawn units
    // UE_LOG(LogTemp, Warning, TEXT("HostStationEnergy %i"), ThisHostStation->HostStationEnergy);
    if(ThisHostStation->HostStationEnergy > ThisHostStation->TankUnitCost)
    {
      SpawnTank();
    }



  }
}
void AHostStationAIController::BeginPlay()
{
  Super::BeginPlay();
}

TArray<ATankUnit*> AHostStationAIController::GetTankUnitsOnThisTeam()
{
  // get all units on this team
  TArray<AActor*> ActorsWithTag;

  UGameplayStatics::GetAllActorsOfClassWithTag(
      GetWorld(),
      ATankUnit::StaticClass(),
      FName("vehicletag"),
      ActorsWithTag);

  // UE_LOG(LogTemp, Warning, TEXT("%i host station vehicles"), ThisTeam);
  TArray<ATankUnit*> TanksOnThisTeam;
  for(auto& _Actor : ActorsWithTag)
  {
    if (Cast<AVehicleBase>(_Actor)->GetTeam() == ThisTeam)
    {
      TanksOnThisTeam.Add(Cast<ATankUnit>(_Actor));
    }
  }

  return TanksOnThisTeam;
}
void AHostStationAIController::SpawnTank()
{
  FHitResult HitResult;

  FVector AimDirection = ThisHostStation->ArrowToGround->GetForwardVector();

  float RandomNum1 = UKismetMathLibrary::RandomFloat();
  RandomNum1-=0.5;
  RandomNum1*=1.0;

  float RandomNum2 = UKismetMathLibrary::RandomFloat();
  RandomNum2-=0.5;
  RandomNum2*=1.0;

  float RandomNum3 = UKismetMathLibrary::RandomFloat();
  RandomNum3-=0.5;
  RandomNum3*=1.0;

  AimDirection.X += RandomNum1;
  AimDirection.Y += RandomNum2;
  AimDirection.Z += RandomNum3;


  bool HitSomething = GetWorld()->LineTraceSingleByChannel(
      HitResult, // Out hit
      ThisHostStation->ArrowToGround->GetComponentLocation(),
      ThisHostStation->ArrowToGround->GetComponentLocation() + 100000*AimDirection,
      ECollisionChannel::ECC_Visibility
      );

  DrawDebugLine(
      GetWorld(),
      HitResult.Location,
      HitResult.Location+FVector(0,0,500),
      FColor(0,0,0),
      true,
      1.,
      1,
      100
      );

  UCanSpawnUnits* SpawnUnitsComponent = ThisHostStation->FindComponentByClass<UCanSpawnUnits>();

  HitResult.Location.Z+=300;
  SpawnUnitsComponent->AISpawnThingAtLocation(HitResult.Location);
  ThisHostStation->HostStationEnergy -= ThisHostStation->TankUnitCost;
}
void AHostStationAIController::OrderVehicleAttackNearestEnemy(ATankUnit* TankUnit)
{
  // UE_LOG(LogTemp, Warning, TEXT("OrderVehicleAttackNearestEnemy"));
  // find location of nearest enemy vehicle
  AActor* NearestTarget = Cast<AMyAIController>(TankUnit->GetController())->FindNearestTarget();
  // UE_LOG(LogTemp, Warning, TEXT("AAAAM not calling"));
  Cast<AMyAIController>(TankUnit->GetController())->MoveToActor(NearestTarget, 100);
  // target nearest enemy
  // TankUnit->MoveToLocationComponent->CreateMoveMarker(NearestTarget->GetActorLocation());
}
void AHostStationAIController::CaptureNearestTile(ATankUnit* TankUnit)
{
  if(TankUnit!=nullptr)
  {
    // UE_LOG(LogTemp, Warning, TEXT("%s CaptureNearestTile called"), *TankUnit->GetName());
    // find the nearest tile
    TArray<AActor*> ActorsFound;
    UGameplayStatics::GetAllActorsOfClass(
        GetWorld(),
        ACapturableGridPoint::StaticClass(),
        ActorsFound
        );

    float ClosestDistance = 999999999;
    AActor* NearestTile = nullptr;
    FVector ThisVehicleLoation = TankUnit->GetActorLocation();
    for(auto& _Actor : ActorsFound){
      FVector ThisTileLocation = _Actor->GetActorLocation();
      float Distance = FVector::Dist(ThisTileLocation, ThisVehicleLoation);
      if(Distance < ClosestDistance)
      {
        // check if this tile belongs to the vehicle team
        int32 TileTeam = Cast<ACapturableGridPoint>(_Actor)->GetTeam();
        if(TileTeam!=TankUnit->Team)
        {

          // check if there is a vehicle from this team already on the point
          bool IsTeamMateOnpoint = 0;
          for(auto& _Vehicle : Cast<ACapturableGridPoint>(_Actor)->VehiclesOnGridPoint)
          {
            if(_Vehicle->Team==TankUnit->Team && _Vehicle!=TankUnit)
            {
              // a team mate is already on this point
              IsTeamMateOnpoint = 1;
            }
          }
          if(!IsTeamMateOnpoint)
          {
            ClosestDistance = Distance;
            NearestTile = _Actor;
          }


        }
      }

    }
    // move to this tile
    if(NearestTile!=nullptr)
    {
      DrawDebugLine(
          GetWorld(),
          NearestTile->GetActorLocation(),
          NearestTile->GetActorLocation()+FVector(0,0,400),
          // 100*(CurrentLocation+ForwardVec),
          FColor(255,0,0), // color
          true, //persitent
          1.,// lifetime
          1,// depth priority
          40 // thickness
          );
      if(TankUnit->GetController()!=nullptr)
      {
        Cast<AMyAIController>(TankUnit->GetController())->MoveToActorAndStop(NearestTile);
      }
    }
  }

}
