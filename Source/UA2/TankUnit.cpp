// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "wheel.h"
#include "MyAIController.h"
#include "TankUnit.h"
#include "MoveToLocationMarker.h"
#include "MovementWaypoint.h"
#include "UA2navcomponent_ground_vehicle.h"
#include "TurretComponent.h"
#include "FloatingVehicleWidgetC.h"

// Sets default values
ATankUnit::ATankUnit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
        // movement component
        MoveToLocationComponent = CreateDefaultSubobject<UMoveToLocationMarker>(FName("MoveToLocationComponent"));
        MoveToLocationComponent->RegisterParent(Cast<AVehicleBase>(this));
        NavigationComponent = CreateDefaultSubobject<UUA2navcomponent_ground_vehicle>(FName("NavigationComponent"));
        TurretComponent = CreateDefaultSubobject<UTurretComponent>(FName("TurretComponent"));
}
// Called when the game starts or when spawned
void ATankUnit::BeginPlay()
{
  Super::BeginPlay();


  // // look for controller
  // AController* ThisAIController = GetController();
  // UE_LOG(LogTemp, Warning, TEXT("%s finding ai controller"), *GetName());

  // if(ThisAIController != nullptr)
  // {
  //   UE_LOG(LogTemp, Warning, TEXT("found ai controller: %s"), *ThisAIController->GetName());
  // }
  // else
  // {
  //   UE_LOG(LogTemp, Warning, TEXT("could not find ai controller"));

  // }


}
// Called every frame
void ATankUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
        // GetName()
        // UE_LOG(LogTemp, Warning, TEXT("%s: I am on team %i"), *GetName(), Team);

        // // get the mouse position
        // float LocationX, LocationY;
        // GetWorld()->GetFirstPlayerController()->GetMousePosition(LocationX, LocationY);

        // FVector2D MousePosition(LocationX, LocationY);
        // FHitResult HitResult;
        // const bool bTraceComplex = false;

        // UE_LOG(LogTemp, Warning, TEXT("MousePosition: %s"), *MousePosition.ToString());

        // GetWorld()->GetFirstPlayerController()->GetHitResultAtScreenPosition(
        //     MousePosition, ECC_Visibility, bTraceComplex, HitResult
        //     );

        // UE_LOG(LogTemp, Warning, TEXT("HitResult: "), *HitResult.TraceEnd.ToString());


}
// Called to bind functionality to input
void ATankUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
void ATankUnit::ControlWheels(float ForwardValue, float RightValue)
{

  float FrontRightWheelValue = 0.0;
  float FrontLeftWheelValue = 0.0;
  float BackRightWheelValue = 0.0;
  float BackLeftWheelValue = 0.0;
  TArray<float*> DriveValues;
  DriveValues.Add(&FrontRightWheelValue);
  DriveValues.Add(&FrontLeftWheelValue);
  DriveValues.Add(&BackRightWheelValue);
  DriveValues.Add(&BackLeftWheelValue);


  if(ForwardValue>0.1)
  {
    // move forward
    FrontRightWheelValue+=ForwardValue;
    FrontLeftWheelValue+=ForwardValue;
    BackRightWheelValue+=ForwardValue;
    BackLeftWheelValue+=ForwardValue;
  }
  if(ForwardValue<-0.1)
  {
    // move backward
    FrontRightWheelValue+=ForwardValue;
    FrontLeftWheelValue+=ForwardValue;
    BackRightWheelValue+=ForwardValue;
    BackLeftWheelValue+=ForwardValue;
  }
  if(RightValue > 0.1)
  {
    // turn left
    FrontRightWheelValue-=RightValue;
    FrontLeftWheelValue+=RightValue;
    BackRightWheelValue-=RightValue;
    BackLeftWheelValue+=RightValue;
  }
  if(RightValue < -0.1)
  {
    // turn right
    FrontRightWheelValue-=RightValue;
    FrontLeftWheelValue+=RightValue;
    BackRightWheelValue-=RightValue;
    BackLeftWheelValue+=RightValue;
  }

  // make sure all the values are less than 1.0
  for(auto& _DriveValue : DriveValues)
  {
    if(abs(*_DriveValue) > 1.0)
    {
      *_DriveValue = *_DriveValue / abs(*_DriveValue);
    }
  }

  FrontRightWheel->DriveWheel(FrontRightWheelValue);
  FrontLeftWheel->DriveWheel(FrontLeftWheelValue);
  BackRightWheel->DriveWheel(BackRightWheelValue);
  BackLeftWheel->DriveWheel(BackLeftWheelValue);


}
void ATankUnit::PrintActors(TArray<AActor*> ActorArray)
{
  // UE_LOG(LogTemp, Warning, TEXT("PrintActors Called"));

  int32 i = 1;
  for(auto& _Actor : ActorArray){
    FString actorname = _Actor->GetName();
    UE_LOG(LogTemp, Warning, TEXT("ActorName:(%i) %s"), i, *actorname);
    i++;
  }
}
void ATankUnit::PossessPawn(int32 PawnNumber)
{
  UE_LOG(LogTemp, Warning, TEXT("Possessing Pawn %i"), PawnNumber);
}
void ATankUnit::SwitchPawn()
{
  // same thing
  APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

  // PlayerController->DeprojectMousePositionToWorld
  // APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

  // UWorld* world = GetWorld();
  // world->GetFirstPlayerController();

  // GetAllActorsOfClass();
  TArray<AActor*> ActorsFound;
  UGameplayStatics::GetAllActorsOfClass(
      GetWorld(),
      MovingVehicle_BP,
      ActorsFound
      );
  PrintActors(ActorsFound);

  // switch to pawn
  PlayerController->Possess(Cast<APawn>(ActorsFound[1]));
  UE_LOG(LogTemp, Warning, TEXT("possessed pawn 400 in c++"));
  // ActorsFound
  ActorsFound.Num();
  UE_LOG(LogTemp, Warning, TEXT("ActorsFound size: %i"), ActorsFound.Num());

  // TODO: make this possess a pawn
  // PlayerController->Possess()
  // APlayerController
}


void ATankUnit::FindComponents(UStaticMeshComponent* TurretBase_in, UStaticMeshComponent* Barrel_in, Awheel* FrontRightWheel_in, Awheel* FrontLeftWheel_in, Awheel* BackRightWheel_in, Awheel* BackLeftWheel_in, AActor* FirstPersonCameraIn)
{
  this->TurretComponent->TurretBase = TurretBase_in;
  this->TurretComponent->Barrel = Barrel_in;
  this->TurretComponent->ParentActor = this;
  this->TurretComponent->ProjectileBluePrint = ProjectileBluePrint;
  this->TurretComponent->MinPitch = -20;
  this->TurretComponent->MaxPitch = 80;


  this->FrontRightWheel = FrontRightWheel_in;
  this->FrontLeftWheel = FrontLeftWheel_in;
  this->BackRightWheel = BackRightWheel_in;
  this->BackLeftWheel = BackLeftWheel_in;

  this->FirstPersonCamera = FirstPersonCameraIn;
}
void ATankUnit::HandleLeftMouseClick()
{
  APlayerController* ThePlayerController = Cast<APlayerController>(GetController());
  // if the mouse cursow is shown
  if(ThePlayerController->bShowMouseCursor)
  {
    // spawn a vehicle
  }
  else
  {
    TurretComponent->FireCannon(this->Team);
  }

}

void ATankUnit::Reposess()
{
  // if this was controlled by player, it doesnt have an ai controller yet
  if(ThisAIController==nullptr)
  {
    SpawnDefaultController();
    UE_LOG(LogTemp, Warning, TEXT("SpawnDefaultController called"));
    ThisAIController = Cast<AAIController>( GetController() );

  }
  UE_LOG(LogTemp, Warning, TEXT("repossess called %s"), *ThisAIController->GetName());
  ThisAIController->Possess(this);


}
void ATankUnit::SwitchCameraView()
{

  APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
  if(!InFirstPersonView)
  {
    PlayerController->SetViewTargetWithBlend(FirstPersonCamera);
    InFirstPersonView = 1;
  }
  else
  {
    PlayerController->SetViewTargetWithBlend(this);
    InFirstPersonView = 0;
  }
}
void ATankUnit::SetCameraToCurrentView()
{
  APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
  if(InFirstPersonView)
  {
    PlayerController->SetViewTargetWithBlend(FirstPersonCamera);
  }
}
