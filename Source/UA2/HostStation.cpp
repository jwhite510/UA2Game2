// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStation.h"
#include "MyAIController.h"
#include "DrawDebugHelpers.h"
#include "CanSpawnUnits.h"
#include "TankUnit.h"

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
    SpawnUnitsComponent->SpawnThingAtLocation();

  }
}
