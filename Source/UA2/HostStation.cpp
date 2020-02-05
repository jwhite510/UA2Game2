// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStation.h"
#include "MyAIController.h"
#include "DrawDebugHelpers.h"
#include "CanSpawnUnits.h"
#include "TankUnit.h"
// #include "Runtime/Engine/Classes/Kismet/KismetInputLibrary.h"
// #include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

// Sets default values
AHostStation::AHostStation()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void AHostStation::BeginPlay()
{
	Super::BeginPlay();
}
void AHostStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
        float TimeNow = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
        if((TimeNow - LastIncrementTime) > EnergyIncrementTime)
        {
          LastIncrementTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
          HostStationEnergy+=(1+OwnedTiles);
        }

}
void AHostStation::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
void AHostStation::HandleLeftMouseClick()
{
  // APlayerController* ThePlayerController = Cast<APlayerController>(GetController());
  // if the mouse cursow is shown
  if(SpawnState)
  {
    // ComponentSpawnThing();
    UCanSpawnUnits* SpawnUnitsComponent = FindComponentByClass<UCanSpawnUnits>();
    if(HostStationEnergy > 10)
    {
      SpawnUnitsComponent->SpawnThingAtLocation();
      HostStationEnergy-=10;
    }

  }
}
