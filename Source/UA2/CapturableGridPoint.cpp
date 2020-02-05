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



  int32 team1vehicles = 0;
  int32 team2vehicles = 0;
  // UE_LOG(LogTemp, Warning, TEXT("vehicles on point %s:"), *GetName());
  for(auto& _Vehicle : VehiclesOnGridPoint )
  {
    if(_Vehicle!=nullptr)
    {
      // UE_LOG(LogTemp, Warning, TEXT("VehiclesOnGridPoint:%s"), *_Vehicle->GetName());
      // UE_LOG(LogTemp, Warning, TEXT("VehicleTeam:%i"), _Vehicle->GetTeam());
      // add number for each vehicle
      if(_Vehicle->GetTeam() == 1)
      {
        team1vehicles++;
      }
      else if(_Vehicle->GetTeam() == 2)
      {
        team2vehicles++;
      }

    }
  }
  // the color defaults to being neutral
  float color_target = 0.5;
  if(VehiclesOnGridPoint.Num()!=0)
  {
    // calculate weighted average
    color_target = (0*team1vehicles + 1*team2vehicles);
    color_target/=VehiclesOnGridPoint.Num();
  }

  if(!IsOwned)
  {
    // set material color_target
    UE_LOG(LogTemp, Warning, TEXT("%s color_target:%f"), *GetName(), color_target);
    UE_LOG(LogTemp, Warning, TEXT("%s blend:%f"), *GetName(), blend);

    if (color_target < blend)
    {
      blend -= 0.1 * DeltaTime;
    }
    else if (color_target > blend)
    {
      blend += 0.1 * DeltaTime;
    }

    // check if point has been captured
    if(blend<=0)
    {
      UE_LOG(LogTemp, Warning, TEXT("point captured %f"), blend);
      IsOwned = 1;
    }
    else if (blend>=1)
    {
      UE_LOG(LogTemp, Warning, TEXT("point captured %f"), blend);
      IsOwned = 1;
    }
  }


  // blend = color;
  DynamicMaterial->SetScalarParameterValue(TEXT("Blend"), blend);
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
