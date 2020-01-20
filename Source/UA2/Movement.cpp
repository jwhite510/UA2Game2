// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement.h"

// Sets default values for this component's properties
UMovement::UMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMovement::initialize(UStaticMeshComponent* body)
{
  this->body = body;
  UE_LOG(LogTemp, Warning, TEXT("initialize called"));
}

void UMovement::MoveForce()
{
  UE_LOG(LogTemp, Warning, TEXT("MoveForce called"));

}

