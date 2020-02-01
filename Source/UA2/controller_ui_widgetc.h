// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "controller_ui_widgetc.generated.h"

class AVehicleBase;
class AUAVehiclePlayerController;

/**
 * 
 */
UCLASS()
class UA2_API Ucontroller_ui_widgetc : public UUserWidget
{
	GENERATED_BODY()

  public:
        UFUNCTION(BluePrintCallable, Category="MapControl")
        void Magic(UCanvasPanelSlot* CanvaSslot, FString ButtonName);

        UFUNCTION(BluePrintCallable, Category="MapControl")
        void Call_On_Tick();

        UFUNCTION(BluePrintCallable, Category="MapControl")
        void C_Mouse_Button_Up();

        FVector2D GetPositionOnMap(UCanvasPanelSlot* CanvaSslot);
        FVector2D OriginalClickPosition;
        UCanvasPanelSlot* RefCanvasSlot = nullptr;

        AActor* PlayerCamera = nullptr;
        FVector OriginalCameraPosition;

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=AnchorData)
        UWidget* SpawnUnitsCursorCC;

        UFUNCTION(BluePrintCallable, Category="Clicked")
        void SpawnUnitsButtonClicked();

        FVector2D GetActualMousePosition();

        // selected vehicle
        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=AnchorData)
        FString SelectedVehicleName = "None";

        AVehicleBase* SelectedVehicle;

        FString ButtonClicked;


        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Controller")
        AUAVehiclePlayerController* ThisPlayerController;




  private:
        bool IsMouseDragging = 0;
        bool IsMouseDown = 0;
        float InitialClickTime;



	
};
