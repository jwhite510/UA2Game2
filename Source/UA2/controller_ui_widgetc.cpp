// Fill out your copyright notice in the Description page of Project Settings.


#include "controller_ui_widgetc.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"




void Ucontroller_ui_widgetc::Magic(UCanvasPanelSlot* CanvaSslot)
{

  OriginalClickPosition = GetPositionOnMap(CanvaSslot);
  RefCanvasSlot = CanvaSslot;
  // set mouse draggint to true
  IsMouseDragging = 1;


}
void Ucontroller_ui_widgetc::Call_On_Tick()
{
  if ( IsMouseDragging )
  {
    if(RefCanvasSlot!=nullptr)
    {
      FVector2D WidgetLocation = GetPositionOnMap(RefCanvasSlot);
      UE_LOG(LogTemp, Warning, TEXT("WidgetLocation: %s"), *WidgetLocation.ToString());
      UE_LOG(LogTemp, Warning, TEXT("OriginalMouseClick: %s"), *OriginalClickPosition.ToString());

    }
  }
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
