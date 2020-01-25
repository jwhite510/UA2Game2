// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "controller_ui_widgetc.generated.h"

/**
 * 
 */
UCLASS()
class UA2_API Ucontroller_ui_widgetc : public UUserWidget
{
	GENERATED_BODY()

  public:
        UFUNCTION(BluePrintCallable, Category="MapControl")
        void Magic(UCanvasPanelSlot* CanvaSslot);

        UFUNCTION(BluePrintCallable, Category="MapControl")
        void Call_On_Tick();

        UFUNCTION(BluePrintCallable, Category="MapControl")
        void C_Mouse_Button_Up();

  private:
        bool IsMouseDragging = 0;



	
};
