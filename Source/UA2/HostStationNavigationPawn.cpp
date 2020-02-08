// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStationNavigationPawn.h"
#include "HostStation.h"
#include "HostStationNavMovementComponent.h"

// Sets default values
AHostStationNavigationPawn::AHostStationNavigationPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
        NavigationComponent = CreateDefaultSubobject<UHostStationNavMovementComponent>(FName("HostStationNavigationComponent"));

}

// Called when the game starts or when spawned
void AHostStationNavigationPawn::BeginPlay()
{
	Super::BeginPlay();
        UE_LOG(LogTemp, Warning, TEXT("HostStationNavigationPawn initialized"));
}

// Called every frame
void AHostStationNavigationPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHostStationNavigationPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHostStationNavigationPawn::RegisterParentHoststation(AHostStation* ParentHostStationIn)
{
  UE_LOG(LogTemp, Warning, TEXT("%s RegisterParentHoststation called"), *ParentHostStationIn->GetName());
  ParentHostStation = ParentHostStationIn;
}
