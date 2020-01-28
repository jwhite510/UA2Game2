// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementWaypoint.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMovementWaypoint::AMovementWaypoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
        SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("SceneComponent"));

}

// Called when the game starts or when spawned
void AMovementWaypoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovementWaypoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
        DrawDebugLine(
            GetWorld(),
            GetActorLocation(),
            GetActorLocation()+FVector(0,0,400),
            // 100*(CurrentLocation+ForwardVec),
            FColor(0,0,255), // color
            true, //persitent
            1.,// lifetime
            1,// depth priority
            20 // thickness
            );

}

