// Fill out your copyright notice in the Description page of Project Settings.


#include "CapturableGridPoint.h"
#include "VehicleBase.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"



// Sets default values
ACapturableGridPoint::ACapturableGridPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
        // CaptureVolume->OnComponentBeginOverlap.AddDynamic(this, &ACapturableGridPoint::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ACapturableGridPoint::BeginPlay()
{
	Super::BeginPlay();
        UMaterialInterface* Material = Tile->GetMaterial(0);
        DynamicMaterial = UMaterialInstanceDynamic::Create(Material, NULL);
        Tile->SetMaterial(0, DynamicMaterial);
}

// Called every frame
void ACapturableGridPoint::Tick(float DeltaTime)
{

  Super::Tick(DeltaTime);

  // set material color
  float blend = 0.5f + FMath::Cos(GetWorld()->TimeSeconds)/2;
  DynamicMaterial->SetScalarParameterValue(TEXT("Blend"), blend);


  UE_LOG(LogTemp, Warning, TEXT("vehicles on point %s:"), *GetName());
  for(auto& _Vehicle : VehiclesOnGridPoint )
  {
    if(_Vehicle!=nullptr)
    {
      UE_LOG(LogTemp, Warning, TEXT("VehiclesOnGridPoint:%s"), *_Vehicle->GetName());
    }
  }

}

void ACapturableGridPoint::OverLapBegin(AActor* OverlappingActor)
{
  AVehicleBase* OverlappingVehicle = FindOverlappingVehicle(OverlappingActor);
  if(OverlappingVehicle!=nullptr)
  {
    // check if vehicle is in list, if not add it
    bool FoundVehicle = 0;
    for(auto& _Vehicle : VehiclesOnGridPoint ){
      if(_Vehicle == OverlappingVehicle)
      {
        FoundVehicle = 1;
        break;
      }
    }
    if(!FoundVehicle)
    {
      VehiclesOnGridPoint.Add(OverlappingVehicle);
    }
  }
}
AVehicleBase* ACapturableGridPoint::FindOverlappingVehicle(AActor* OverlappingActorIn)
{
  // AVehicleBase* OverlappingActorParent = Cast<AVehicleBase>(OverlappingActorIn->GetParentActor());
  AVehicleBase* OverlappingActor = Cast<AVehicleBase>(OverlappingActorIn);

  // if(OverlappingActorParent!=nullptr)
  // {
    // return OverlappingActorParent;

  // }
  if (OverlappingActor!=nullptr)
  {
    return OverlappingActor;

  }
  return nullptr;
}
void ACapturableGridPoint::OverLapEnd(AActor* OverlappingActor)
{
    VehiclesOnGridPoint.Remove(Cast<AVehicleBase>(OverlappingActor));
}
