// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldClickedLocation.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "VehicleBase.h"

// Sets default values
AWorldClickedLocation::AWorldClickedLocation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
        SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("SceneComponent"));
        SetRootComponent(SceneComponent);

}

// Called when the game starts or when spawned
void AWorldClickedLocation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorldClickedLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor* AWorldClickedLocation::FindNearestActor()
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
  float ClosestDistance = 500;
  for(auto& _Actor : ActorsWithTag){

    AVehicleBase* FoundActorVehicle = Cast<AVehicleBase>(_Actor);

    // get distance
    FVector TargetActorLocation = FoundActorVehicle->GetActorLocation();
    FVector ThisActorLocation = GetActorLocation();
    float Distance = FVector::Dist(TargetActorLocation, ThisActorLocation);

    // check if this is the closest and not on the same team
    // if (Distance < ClosestDistance && FoundActorVehicle->GetTeam()!=_ControllerPawn->GetTeam())
    if (Distance < ClosestDistance )
    {
      TargetActor = FoundActorVehicle;
      ClosestDistance = Distance;
    }
  }
  return TargetActor;
}
