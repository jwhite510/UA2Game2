// Fill out your copyright notice in the Description page of Project Settings.


#include "controller_ui_widgetc.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#include "HostStation.h"
#include "DrawDebugHelpers.h"
#include "WorldClickedLocation.h"
#include "Runtime/Engine/Classes/Kismet/KismetInputLibrary.h"
#include "TankUnit.h"
#include "MoveToLocationMarker.h"



void Ucontroller_ui_widgetc::Magic(UCanvasPanelSlot* CanvaSslot, FString ButtonName)
{

  OriginalClickPosition = GetPositionOnMap(CanvaSslot);
  RefCanvasSlot = CanvaSslot;
  // set mouse draggint to true
  IsMouseDown = 1;
  // get current time
  InitialClickTime = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());

  // find target
  TArray<AActor*> ActorsWithTag;
  UGameplayStatics::GetAllActorsWithTag(
      GetWorld(),
      FName("PlayerCamera"),
      ActorsWithTag
      );
  PlayerCamera = ActorsWithTag[0];
  OriginalCameraPosition = PlayerCamera->GetActorLocation();
  this->ButtonClicked = ButtonName;
}
void Ucontroller_ui_widgetc::Call_On_Tick()
{
  if ( IsMouseDown )
  {
    float TimeNow = UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld());
    float TimeMouseHeld = TimeNow - InitialClickTime;
    // UE_LOG(LogTemp, Warning, TEXT("TimeMouseHeld: %f"), TimeMouseHeld);
    if(TimeMouseHeld > 0.1)
    {
      IsMouseDragging = 1;
      // move player camera
      if(RefCanvasSlot!=nullptr)
      {
        FVector2D WidgetLocation = GetPositionOnMap(RefCanvasSlot);
        FVector2D MouseMovement = WidgetLocation - OriginalClickPosition;

        // UE_LOG(LogTemp, Warning, TEXT("MouseMovement: %s"), *MouseMovement.ToString());
        FVector CurrentCameraPosition = OriginalCameraPosition;

        // add movement to camera position
        CurrentCameraPosition.Y -= 6000*MouseMovement.X;
        CurrentCameraPosition.X += 6000*MouseMovement.Y;

        PlayerCamera->SetActorLocation(
           CurrentCameraPosition
           );

        // UE_LOG(LogTemp, Warning, TEXT("WidgetLocation: %s"), *WidgetLocation.ToString());
        // UE_LOG(LogTemp, Warning, TEXT("OriginalMouseClick: %s"), *OriginalClickPosition.ToString());
      }
    }
  }
  // make the spawn cursor follow mouse
  // UE_LOG(LogTemp, Warning, TEXT("on tick running"));
  UCanvasPanelSlot* Ucs = Cast<UCanvasPanelSlot>(SpawnUnitsCursorCC->Slot);
  // move
  FVector2D MouseScreenPositionIn = GetActualMousePosition();
  MouseScreenPositionIn.X += 10;
  MouseScreenPositionIn.Y += 10;
  Ucs->SetPosition(MouseScreenPositionIn);

}
void Ucontroller_ui_widgetc::C_Mouse_Button_Up()
{

  if(IsMouseDragging==0)
  {
    if(RefCanvasSlot!=nullptr)
    {

      // get world mouse click location
      // ortho width of camera:
      float OrthoWidth = 5000.0;
      FVector2D WorldMapClickLocation = OrthoWidth*(GetPositionOnMap(RefCanvasSlot));
      FVector WorldMapClickLocationFV;
      WorldMapClickLocationFV.X = -WorldMapClickLocation.Y;
      WorldMapClickLocationFV.Y = WorldMapClickLocation.X;
      WorldMapClickLocationFV.Z = 0;
      FVector WorldClickLocation = WorldMapClickLocationFV+OriginalCameraPosition;

      // make line trace
      FHitResult HitResult;
      FVector StartLocation;
      FVector EndLocation;
      bool HitSomething = GetWorld()->LineTraceSingleByChannel(
          HitResult, // Out hit
          // StartLocation, // start
          // EndLocation, // end
          WorldClickLocation, // start
          WorldClickLocation+FVector(0,0,-10000000), // end
          ECollisionChannel::ECC_Visibility
          );

      if(ButtonClicked=="Left Mouse button")
      {
        SelectVehicle(HitResult);
      }
      else if (ButtonClicked=="Right Mouse button")
      {
        MoveOrder(HitResult);
      }
    }

  }


  // UE_LOG(LogTemp, Warning, TEXT("mouse up called"));
  IsMouseDown = 0;
  IsMouseDragging=0;
}
FVector2D Ucontroller_ui_widgetc::GetPositionOnMap(UCanvasPanelSlot* CanvaSslot)
{
  // get player controller
  APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

  // get mouse position of player
  float LocationX;
  float LocationY;
  PlayerController->GetMousePosition(LocationX, LocationY);
  FVector2D MouseScreenPositionIn(LocationX, LocationY);

  // get viewport size
  FVector2D ViewPortSizeIn = UWidgetLayoutLibrary::GetViewportSize(GetWorld());

  // get viewport scale
  float viewport_scale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());

  ViewPortSizeIn = ViewPortSizeIn / viewport_scale;
  MouseScreenPositionIn = MouseScreenPositionIn / viewport_scale;


  // get size
  FVector2D MapSizeIn = CanvaSslot->GetSize();
  FVector2D SPositionIn = CanvaSslot->GetPosition();
  FAnchors AnchorIn = CanvaSslot->GetAnchors();

  // position of anchor in local coordinates
  FVector2D Anch_local = ViewPortSizeIn*AnchorIn.Minimum;
  // float Anch_local_y = ViewPortSizeIn.Y*Anchor.Y;

  FVector2D Widgetpos = SPositionIn + Anch_local;

  // gets the current location on the map (normalized)

  return ((MouseScreenPositionIn - Widgetpos) / MapSizeIn)-0.5;
}

void Ucontroller_ui_widgetc::SpawnUnitsButtonClicked()
{
  // mouse invisible
  APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  AHostStation* PawnHostStation = Cast<AHostStation>(PlayerController->GetPawn());
  if(PawnHostStation!=nullptr)
  {
    if(PawnHostStation->SpawnState==0)
    {
      SpawnUnitsCursorCC->SetVisibility(ESlateVisibility::Visible);
      PawnHostStation->SpawnState = 1;
    }
  }
}
FVector2D Ucontroller_ui_widgetc::GetActualMousePosition()
{
  // get mouse position
  APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  // get viewport scale
  float viewport_scale = UWidgetLayoutLibrary::GetViewportScale(GetWorld());

  // get mouse position of player
  float LocationX;
  float LocationY;
  PlayerController->GetMousePosition(LocationX, LocationY);
  FVector2D MouseScreenPositionIn(LocationX, LocationY);
  MouseScreenPositionIn = MouseScreenPositionIn / viewport_scale;
  return MouseScreenPositionIn;
}
void Ucontroller_ui_widgetc::SelectVehicle(FHitResult HitResult)
{
        UE_LOG(LogTemp, Warning, TEXT("SelectVehicle function"));
        // try to print actor
        if(HitResult.GetActor()!=nullptr)
        {
          UE_LOG(LogTemp, Warning, TEXT("hit actor:%s"), *HitResult.GetActor()->GetName());
        }

        // draw sphere at hit location
        // DrawDebugSphere(
        //     GetWorld(),
        //     HitResult.Location,
        //     500, // radius
        //     20, // segments
        //     FColor(0,255,0), // color
        //     1 // persistent lines
        //     );

        // spawn an actor at this location, search for nearest actors that are vehicles
        AActor* SpawnedWorldClickLActor = GetWorld()->SpawnActor<AActor>(
            AWorldClickedLocation::StaticClass(),
            HitResult.Location,
            FRotator(0,0,0)
            );
        UE_LOG(LogTemp, Warning, TEXT("HitResult.Location:%s"), *HitResult.Location.ToString());
        AWorldClickedLocation* SpawnedWorldClickL = Cast<AWorldClickedLocation>(SpawnedWorldClickLActor);
        AActor* FoundActor =  SpawnedWorldClickL->FindNearestActor();
        if(FoundActor!=nullptr)
        {
          FoundActor->GetName();
          UE_LOG(LogTemp, Warning, TEXT("FoundActor:%s"), *FoundActor->GetName());
          // set variable
          SelectedVehicleName = FoundActor->GetName();
          SelectedVehicle = Cast<AVehicleBase>(FoundActor);

        }
        UE_LOG(LogTemp, Warning, TEXT("destroy actor called"));
        SpawnedWorldClickL->Destroy();

}
void Ucontroller_ui_widgetc::MoveOrder(FHitResult HitResult)
{
  UE_LOG(LogTemp, Warning, TEXT("send move command to unit"));
  if(SelectedVehicle!=nullptr)
  {
    UE_LOG(LogTemp, Warning, TEXT("%s"), *SelectedVehicle->GetName());
    ATankUnit* SelectedTank = Cast<ATankUnit>(SelectedVehicle);
    if(SelectedTank!=nullptr)
    {
      SelectedTank->MoveToLocationComponent->CreateMoveMarker(HitResult.Location);
      UE_LOG(LogTemp, Warning, TEXT("move marker to: %s"), *HitResult.Location.ToString());
    }
  }
}
void Ucontroller_ui_widgetc::FindPlayerHostStation(int32 TeamIn)
{
  TArray<AActor*> ActorsFound;
  UGameplayStatics::GetAllActorsOfClass(
      GetWorld(),
      AHostStation::StaticClass(),
      ActorsFound
      );
  for(auto& _Actor : ActorsFound)
  {
    if(Cast<AVehicleBase>(_Actor)->Team == TeamIn)
    {
      UE_LOG(LogTemp, Warning, TEXT("PlayerHostStation assigned"));
      PlayerHostStation = Cast<AHostStation>(_Actor);
    }
  }

}
