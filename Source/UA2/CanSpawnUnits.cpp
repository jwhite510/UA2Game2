// Fill out your copyright notice in the Description page of Project Settings.


#include "CanSpawnUnits.h"
#include "DrawDebugHelpers.h"
#include "TankUnit.h"
#include "AIController.h"
#include "VehicleBase.h"

// Sets default values for this component's properties
UCanSpawnUnits::UCanSpawnUnits()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCanSpawnUnits::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCanSpawnUnits::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UCanSpawnUnits::SpawnThingAtLocation()
{
  FVector MouseLocation, MouseDirection;
  APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  PlayerController->DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

  // get hit result
  FHitResult HitResult;
  auto StartLocation = MouseLocation;
  auto EndLocation = MouseLocation + (MouseDirection*100000);

  bool HitSomething = GetWorld()->LineTraceSingleByChannel(
      HitResult, // Out hit
      StartLocation, // start
      EndLocation, // end
      ECollisionChannel::ECC_Visibility);

  // get the state of player controller
  if(HitSomething){


    FVector HitLocation = HitResult.Location;

    // spawn something at this location
    // DrawDebugLine(
    //     GetWorld(),
    //     HitLocation,
    //     HitLocation+FVector(0,0,100),
    //     // 100*(CurrentLocation+ForwardVec),
    //     FColor(255,0,255), // color
    //     true, //persitent
    //     1.,// lifetime
    //     2,// depth priority
    //     20 // thickness
    //     );

    ATankUnit* SpawnedActor = GetWorld()->SpawnActor<ATankUnit>(
        TankUnitBP,
        HitLocation+FVector(0,0,300),
        FRotator(0,0,0)
        );

    AVehicleBase* ThisVehicle = Cast<AVehicleBase>(GetOwner());
    SpawnedActor->SetTeam(ThisVehicle->Team);
    SpawnedActor->SetWidgetTeam();
    SpawnedActor->SpawnDefaultController();
    // destroy the spawn point actor
    AAIController* ThisAIController = Cast<AAIController>( SpawnedActor->GetController() );
    SpawnedActor->RememberAIController(ThisAIController);
  }
}
