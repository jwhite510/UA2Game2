// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UAVehiclePlayerController.generated.h"
class UWidget;
class Ucontroller_ui_widgetc;
/**
 *
 */
UCLASS()
class UA2_API AUAVehiclePlayerController : public APlayerController
{
	GENERATED_BODY()

        UFUNCTION(BluePrintCallable, Category="Control")
        int ToggleMouseCursor();


        public:
        UFUNCTION(BluePrintImplementableEvent, Category="UI Mode")
        void Set_UI_only();

        UFUNCTION(BluePrintImplementableEvent, Category="UI Mode")
        void Set_Game_only();

	virtual void Tick(float DeltaTime) override;

        UFUNCTION(BluePrintCallable, Category="pawn")
        void SetUIForPawn(APawn* NewPawn, UWidget* SpawnUnitButton);


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=AnchorData)
        Ucontroller_ui_widgetc* ControllerUIWidget;

        UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Controller")
        bool UI_enabled;

        UFUNCTION(BluePrintCallable, Category="Input")
        void HandleMouseClick(FString Button);

        void ClickWorld(FString Button);



};
