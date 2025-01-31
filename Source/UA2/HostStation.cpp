// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStation.h"
#include "MyAIController.h"
#include "DrawDebugHelpers.h"
#include "CanSpawnUnits.h"
#include "TankUnit.h"
#include "HostStationNavigationPawn.h"
#include "MoveToLocationMarker.h"
#include "Components/ArrowComponent.h"
#include "TurretComponent.h"
// #include "Runtime/Engine/Classes/Kismet/KismetInputLibrary.h"
// #include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

// Sets default values
AHostStation::AHostStation()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
        MoveToLocationComponent = CreateDefaultSubobject<UMoveToLocationMarker>(FName("MoveToLocationComponent"));
        MoveToLocationComponent->RegisterParent(Cast<AVehicleBase>(this));
        TurretComponent = CreateDefaultSubobject<UTurretComponent>(FName("TurretComponent"));

}
// Called when the game starts or when spawned
void AHostStation::BeginPlay()
{
	Super::BeginPlay();

        // create navigation pawn
        HostSChildNavigationPawn = NewObject<UChildActorComponent>(this);
        HostSChildNavigationPawn->bEditableWhenInherited = true;
        HostSChildNavigationPawn->RegisterComponent();
        HostSChildNavigationPawn->SetChildActorClass(AHostStationNavigationPawn::StaticClass());
        HostSChildNavigationPawn->CreateChildActor();
        Cast<AHostStationNavigationPawn>(HostSChildNavigationPawn->GetChildActor())->RegisterParentHoststation(this);
        HostSChildNavigationPawn->GetChildActor()->SetActorLocation(GetActorLocation());
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

  FHitResult HitResult;
  bool HitSomething = GetWorld()->LineTraceSingleByChannel(
      HitResult, // Out hit
      ArrowToGround->GetComponentLocation(), // start
      ArrowToGround->GetComponentLocation()+100000*ArrowToGround->GetForwardVector(),
      ECollisionChannel::ECC_Visibility);

  // set navigation pawn to this location
  HostSChildNavigationPawn->GetChildActor()->SetActorLocation(HitResult.Location);

  // adjust floating height
  MoveToTargetHeight(HitResult.Location);

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
void AHostStation::MoveToTargetHeight(FVector GroundLocation)
{
  float CurrentHeight = FVector::Dist(GetActorLocation(), GroundLocation);
  float DeltaHeight = TargetFloatingHeight - CurrentHeight;

  if(DeltaHeight>3)
  {
    SetActorLocation(GetActorLocation()+FVector(0,0,1));
  }
  else if (DeltaHeight<-3)
  {
    SetActorLocation(GetActorLocation()+FVector(0,0,-1));
  }
}
void AHostStation::FindComponents(UStaticMeshComponent* TurretBase_in, UStaticMeshComponent* Barrel_in)
{
  this->TurretComponent->TurretBase = TurretBase_in;
  this->TurretComponent->Barrel = Barrel_in;
  this->TurretComponent->MinPitch = -80;
  this->TurretComponent->MaxPitch = 80;
  this->TurretComponent->ParentActor = this;
  this->TurretComponent->ProjectileBluePrint = ProjectileBluePrint;
}
