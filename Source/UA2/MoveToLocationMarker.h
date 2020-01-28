// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveToLocationMarker.generated.h"

class USceneComponent;
class AVehicleBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UA2_API UMoveToLocationMarker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveToLocationMarker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


        void CreateMoveMarker(FVector Location);

        USceneComponent* SceneComponent;

        void RegisterParent(AVehicleBase* _ParentVehicle);
        AVehicleBase* ParentVehicle;
};
