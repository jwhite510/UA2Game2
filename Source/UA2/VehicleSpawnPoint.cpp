// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleSpawnPoint.h"
#include "TankUnit.h"
#include "MyAIController.h"
#include "VehicleBase.h"
#include "CanSpawnUnits.h"
#include "AIController.h"

// Sets default values
AVehicleSpawnPoint::AVehicleSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVehicleSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVehicleSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AVehicleSpawnPoint::Spawn()
{
	FVector Location = GetActorLocation();

        // spawn an actor
        // UE_LOG(LogTemp, Warning, TEXT("SpawnedActor called"));
        AVehicleBase* SpawnedActor = GetWorld()->SpawnActor<AVehicleBase>(
            VehicleToSpawn,
            Location+FVector(0,0,300),
            FRotator(0,0,0)
            );
        // UE_LOG(LogTemp, Warning, TEXT("SetTeam called"));
        SpawnedActor->SetTeam(Team);
        SpawnedActor->SetWidgetTeam();
        SpawnedActor->SpawnDefaultController();
        // // // destroy the spawn point actor
        AAIController* ThisAIController = Cast<AAIController>( SpawnedActor->GetController() );
        SpawnedActor->RememberAIController(ThisAIController);




	Destroy();
}

