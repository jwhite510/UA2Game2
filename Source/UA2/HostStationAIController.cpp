// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStationAIController.h"
#include "HostStation.h"
#include "TankUnit.h"
#include "DrawDebugHelpers.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CanSpawnUnits.h"

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
    }

    // UE_LOG(LogTemp, Warning, TEXT("remove actors from other team"));
    TArray<ATankUnit*> TanksOnThisTeam = GetTankUnitsOnThisTeam();
    for(auto& _Actor : TanksOnThisTeam)
    {
      UE_LOG(LogTemp, Warning, TEXT("_Actor:%s"), *_Actor->GetName());
    }

    // spawn units
    UE_LOG(LogTemp, Warning, TEXT("HostStationEnergy %i"), ThisHostStation->HostStationEnergy);
    if(ThisHostStation->HostStationEnergy > 10)
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
  ThisHostStation->HostStationEnergy -= 10;
}
