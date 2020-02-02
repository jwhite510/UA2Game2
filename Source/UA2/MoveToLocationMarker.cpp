// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToLocationMarker.h"
#include "VehicleBase.h"
#include "TankUnit.h"
#include "MovementWaypoint.h"

// Sets default values for this component's properties
UMoveToLocationMarker::UMoveToLocationMarker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveToLocationMarker::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMoveToLocationMarker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMoveToLocationMarker::CreateMoveMarker(FVector Location)
{

  TArray<AActor*> ChidActors;
  this->ParentVehicle->GetAllChildActors(ChidActors);
  for(auto& _Actor : ChidActors){
    // if there is already a waypoint
    AMovementWaypoint* ChildMovementWaypoint = Cast<AMovementWaypoint>(_Actor);
    if(ChildMovementWaypoint!=nullptr)
    {
      // actor already exists
      ChildMovementWaypoint->Destroy();
      ChildComponent->UnregisterComponent();

      // create new waypoint
      ChildComponent = NewObject<UChildActorComponent>(this);
      ChildComponent->bEditableWhenInherited = true;
      ChildComponent->RegisterComponent();
      ChildComponent->SetChildActorClass(AMovementWaypoint::StaticClass());
      ChildComponent->CreateChildActor();
      ChildComponent->GetChildActor()->SetActorLocation(Location);
      return;
    }

  }

  // if there is no waypoint, create it
  ChildComponent = NewObject<UChildActorComponent>(this);
  ChildComponent->bEditableWhenInherited = true;
  ChildComponent->RegisterComponent();
  ChildComponent->SetChildActorClass(AMovementWaypoint::StaticClass());
  ChildComponent->CreateChildActor();
  ChildComponent->GetChildActor()->SetActorLocation(Location);
  UE_LOG(LogTemp, Warning, TEXT("setting actor location"));

}
void UMoveToLocationMarker::RegisterParent(AVehicleBase* _ParentVehicle)
{
  this->ParentVehicle = _ParentVehicle;
}
