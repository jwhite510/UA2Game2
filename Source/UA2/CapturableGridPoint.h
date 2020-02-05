// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CapturableGridPoint.generated.h"

class AVehicleBase;
class UMaterialInstanceDynamic;

UCLASS()
class UA2_API ACapturableGridPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACapturableGridPoint();

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Capture")
        UStaticMeshComponent* Tile = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

        UFUNCTION(BluePrintCallable, Category="Overlap")
        void OverLapBegin(AActor* OverlappingActor);

        UFUNCTION(BluePrintCallable, Category="Overlap")
        void OverLapEnd(AActor* OverlappingActor);

        AVehicleBase* FindOverlappingVehicle(AActor* OverlappingActor);

        TArray<AVehicleBase*> VehiclesOnGridPoint;

        void UpdateHostStationTiles(int32 DeltaTile);

  private:
        UMaterialInstanceDynamic* DynamicMaterial;

        float CurrentColor = 0.5;

        bool IsOwned = 0;

        int OwningTeam = 999;

};
