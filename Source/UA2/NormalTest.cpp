// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalTest.h"
#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ANormalTest::ANormalTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANormalTest::BeginPlay()
{
	Super::BeginPlay();
        UE_LOG(LogTemp, Warning, TEXT("initialize normaltest cpp"));

}

// Called every frame
void ANormalTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
        FVector CurrentLocation = GetActorLocation();

        if (Cube!=nullptr){
          FVector CubeRight = Cube->GetRightVector().GetSafeNormal();

          DrawDebugLine(
              GetWorld(),
              CurrentLocation,
              CurrentLocation+CubeRight*100,
              FColor(255,0,0),
              true,
              1.,
              1,
              10
              );

        }

        DrawDebugLine(
            GetWorld(),
            CurrentLocation,
            CurrentLocation+FVector(-100, 0, 0),
            FColor(255,0,0),
            true,
            1.,
            1,
            10
            );


}
void ANormalTest::GetComponents(UStaticMeshComponent* Cube)
{
  this->Cube = Cube;
}
