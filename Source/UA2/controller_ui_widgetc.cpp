// Fill out your copyright notice in the Description page of Project Settings.


#include "controller_ui_widgetc.h"




void Ucontroller_ui_widgetc::Magic(float AnchorX, float AnchorY, float ViewPortSizeX, float ViewPortSizeY, float SPositionX, float SPositionY, FVector2D MouseScreenPosition)
{
  UE_LOG(LogTemp, Warning, TEXT("Magic called"));


  // position of anchor in local coordinates
  float Anch_local_x = ViewPortSizeX*AnchorX;
  float Anch_local_y = ViewPortSizeY*AnchorY;

  float WidgetposY = SPositionY + Anch_local_y;
  float WidgetposX = SPositionX + Anch_local_x;

  UE_LOG(LogTemp, Warning, TEXT("ViewPortSizeX: %f"), ViewPortSizeX);
  UE_LOG(LogTemp, Warning, TEXT("ViewPortSizeY: %f"), ViewPortSizeY);

  UE_LOG(LogTemp, Warning, TEXT("MouseScreenPosition.X: %f"), MouseScreenPosition.X);
  UE_LOG(LogTemp, Warning, TEXT("MouseScreenPosition.Y: %f"), MouseScreenPosition.Y);


  UE_LOG(LogTemp, Warning, TEXT("SPositionX: %f"), SPositionX);
  UE_LOG(LogTemp, Warning, TEXT("SPositionY: %f"), SPositionY);

  UE_LOG(LogTemp, Warning, TEXT("Anch_local_y: %f"), Anch_local_y);
  UE_LOG(LogTemp, Warning, TEXT("Anch_local_x: %f"), Anch_local_x);

  UE_LOG(LogTemp, Warning, TEXT("WidgetposY: %f"), WidgetposY);
  UE_LOG(LogTemp, Warning, TEXT("WidgetposX: %f"), WidgetposX);

}


