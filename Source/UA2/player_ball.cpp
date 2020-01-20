// Fill out your copyright notice in the Description page of Project Settings.


#include "player_ball.h"
#include "Components/StaticMeshComponent.h"
#include "Movement.h"
#include "DrawDebugHelpers.h"

// Sets default values
Aplayer_ball::Aplayer_ball()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Aplayer_ball::BeginPlay()
{

	Super::BeginPlay();


}

// Called every frame
void Aplayer_ball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

        // FVector ForceLocation = Body->GetComponentLocation();
        // Body->AddForceAtLocation(FVector(Direction*ForceMovement,0.,0), ForceLocation);

        // FRotator current_rotation = Wheel_LF->GetRelativeRotation();
        // float Current_Pitch = current_rotation.Pitch;
        // float Current_Yaw = current_rotation.Yaw;
        // float Current_Roll = current_rotation.Roll;

        wheel_pitch += 90*DeltaTime;
        if(wheel_pitch > 360.){
          wheel_pitch = 0.;
        }
        FRotator NewRotation = FRotator();
        NewRotation.Pitch = wheel_pitch;
        NewRotation.Yaw = 0;
        NewRotation.Roll = 90;

        UE_LOG(LogTemp, Warning, TEXT("wheel_pitch %f"), wheel_pitch);

        // current_rotation.Pitch += 10.*DeltaTime;
        Wheel_LF->SetRelativeRotation(NewRotation);
        Wheel_2->SetRelativeRotation(NewRotation);
        Wheel_3->SetRelativeRotation(NewRotation);
        Wheel_4->SetRelativeRotation(NewRotation);


}

// Called to bind functionality to input
void Aplayer_ball::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void Aplayer_ball::MoveForward(float Value)
{

  // UE_LOG(LogTemp, Warning, TEXT("MoveForward called %f"), Value);
  Direction = Value;

}
void Aplayer_ball::GetComponents(UStaticMeshComponent* Body, UStaticMeshComponent* Wheel_LF, UStaticMeshComponent* Wheel_2, UStaticMeshComponent* Wheel_3, UStaticMeshComponent* Wheel_4)
{
  this->Body = Body;
  this->Wheel_LF = Wheel_LF;
  this->Wheel_2 = Wheel_2;
  this->Wheel_3 = Wheel_3;
  this->Wheel_4 = Wheel_4;
}

