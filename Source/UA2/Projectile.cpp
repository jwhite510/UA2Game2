// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "VehicleBase.h"

// Sets default values
AProjectile::AProjectile()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
  Super::BeginPlay();
  UE_LOG(LogTemp, Warning, TEXT("Projectile Created"));

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  if(BeginDestroy)
  {
    float TimeNow = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
    if((TimeNow - BeginDestroyTime) > 0.1)
    {
      Destroy();
    }

  }

}

void AProjectile::ProjectileHit(AActor* OtherActor, FVector Impluse)
{
  if(!FirstHit)
  {
    // UE_LOG(LogTemp, Warning, TEXT("Projectile Hit %s, Impulse: %s"), *OtherActor->GetName(), *Impluse.ToString());
    BeginDestroy = 1;
    BeginDestroyTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
    FirstHit = 1;

    // Apply damage
    // find the actor
    AVehicleBase* VehicleToDamage = nullptr;
    if(Cast<AVehicleBase>(OtherActor)!=nullptr)
    {
      if(Cast<AVehicleBase>(OtherActor)->Team != this->Team)
      {
        VehicleToDamage = Cast<AVehicleBase>(OtherActor);
        UE_LOG(LogTemp, Warning, TEXT("Apply Damage to %s"), *Cast<AVehicleBase>(OtherActor)->GetName());
      }
    }
    // check if it has a parent
    else if(Cast<AVehicleBase>(OtherActor->GetParentActor())!=nullptr)
    {
      if(Cast<AVehicleBase>(OtherActor->GetParentActor())->Team != this->Team)
      {
        VehicleToDamage = Cast<AVehicleBase>(OtherActor->GetParentActor());
        UE_LOG(LogTemp, Warning, TEXT("Apply Damage to %s"), *Cast<AVehicleBase>(OtherActor->GetParentActor())->GetName());
      }
    }
  }
}
