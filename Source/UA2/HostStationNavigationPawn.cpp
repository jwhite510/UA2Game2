// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStationNavigationPawn.h"
#include "HostStation.h"
#include "HostStationNavMovementComponent.h"
#include "HostStationNavigationAIControl.h"
#include "DrawDebugHelpers.h"

// Sets default values
AHostStationNavigationPawn::AHostStationNavigationPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
        NavigationComponent = CreateDefaultSubobject<UHostStationNavMovementComponent>(FName("HostStationNavigationComponent"));
        NavigationComponent->FindParent(this);
        // set ai controller class
        AIControllerClass = AHostStationNavigationAIControl::StaticClass();
        SceneComponent = CreateDefaultSubobject<USceneComponent>(FName("SceneComponent"));
        // SetRootComponent(SceneComponent);

}

// Called when the game starts or when spawned
void AHostStationNavigationPawn::BeginPlay()
{
	Super::BeginPlay();
        UE_LOG(LogTemp, Warning, TEXT("HostStationNavigationPawn initialized"));
        // spawn the ai controller
        SpawnDefaultController();
}

// Called every frame
void AHostStationNavigationPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

        if(ParentHostStation!=nullptr)
        {
          // SetActorLocation(ParentHostStation->GetActorLocation());
        }

        // draw a line
        DrawDebugLine(
            GetWorld(),
            GetActorLocation(),
            GetActorLocation()+FVector(0,0,10),
            FColor(255,0,0), // color
            true, //persitent
            1.,// lifetime
            1,// depth priority
            60 // thickness
            );

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
