// Fill out your copyright notice in the Description page of Project Settings.


#include "HostStationAIController.h"
#include "HostStation.h"

void AHostStationAIController::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
  UE_LOG(LogTemp, Warning, TEXT("AHostStationAIController:"));
  AHostStation* ThisHostStation = Cast<AHostStation>(GetPawn());
  if(ThisHostStation!=nullptr)
  {
    if(ThisHostStation->GetTeam() == 1)
    {
      // destroy this controller beause this host station belongs to the player
      Destroy();
    }


  }
}
void AHostStationAIController::BeginPlay()
{
  Super::BeginPlay();
}
