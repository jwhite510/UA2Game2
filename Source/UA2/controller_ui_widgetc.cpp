// Fill out your copyright notice in the Description page of Project Settings.


#include "controller_ui_widgetc.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "HostStation.h"




void Ucontroller_ui_widgetc::Magic(UCanvasPanelSlot* CanvaSslot)
{

  OriginalClickPosition = GetPositionOnMap(CanvaSslot);
  RefCanvasSlot = CanvaSslot;
  // set mouse draggint to true
  IsMouseDragging = 1;
  // find the camera

  // find target
  TArray<AActor*> ActorsWithTag;
  UGameplayStatics::GetAllActorsWithTag(
      GetWorld(),
      FName("PlayerCamera"),
      ActorsWithTag
      );
  PlayerCamera = ActorsWithTag[0];
  OriginalCameraPosition = PlayerCamera->GetActorLocation();
}
void Ucontroller_ui_widgetc::Call_On_Tick()
{
  if ( IsMouseDragging )
  {
    if(RefCanvasSlot!=nullptr)
    {
      FVector2D WidgetLocation = GetPositionOnMap(RefCanvasSlot);
      FVector2D MouseMovement = WidgetLocation - OriginalClickPosition;

      UE_LOG(LogTemp, Warning, TEXT("MouseMovement: %s"), *MouseMovement.ToString());
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


  // make the spawn cursor follow mouse
  // UE_LOG(LogTemp, Warning, TEXT("on tick running"));
  UCanvasPanelSlot* Ucs = Cast<UCanvasPanelSlot>(SpawnUnitsCursorCC->Slot);
  // move
  FVector2D MouseScreenPositionIn = GetActualMousePosition();
  Ucs->SetPosition(MouseScreenPositionIn);

}
void Ucontroller_ui_widgetc::C_Mouse_Button_Up()
{
  UE_LOG(LogTemp, Warning, TEXT("mouse up called"));
  IsMouseDragging = 0;
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
