// Fill out your copyright notice in the Description page of Project Settings.


#include "controller_ui_widgetc.h"




void Ucontroller_ui_widgetc::Magic(FVector2D Anchor, FVector2D ViewPortSize, FVector2D SPosition, FVector2D MouseScreenPosition, FVector2D MapSize)
{
  UE_LOG(LogTemp, Warning, TEXT("Magic called"));


  // position of anchor in local coordinates
  FVector2D Anch_local = ViewPortSize*Anchor;
  // float Anch_local_y = ViewPortSize.Y*Anchor.Y;

  FVector2D Widgetpos = SPosition + Anch_local;

  FVector2D WidgetLocation = (MouseScreenPosition - Widgetpos) / MapSize;

  UE_LOG(LogTemp, Warning, TEXT("WidgetLocation: %s"), *WidgetLocation.ToString());


}


