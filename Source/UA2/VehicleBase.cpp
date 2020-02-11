// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleBase.h"
#include "MyAIController.h"

// Sets default values
AVehicleBase::AVehicleBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVehicleBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AVehicleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AVehicleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AVehicleBase::SetTeam(int32 Team)
{
  this->Team = Team;
  Tags.Add(FName("vehicletag"));
}
void AVehicleBase::RememberAIController(AAIController* _ThisAiController)
{
  ThisAIController = _ThisAiController;
  UE_LOG(LogTemp, Warning, TEXT("remembering ai controller: %s"), *ThisAIController->GetName());
}
int32 AVehicleBase::GetTeam()
{
  // UE_LOG(LogTemp, Warning, TEXT("get team called"));
  return Team;
}
