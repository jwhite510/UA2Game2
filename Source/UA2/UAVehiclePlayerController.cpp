// Fill out your copyright notice in the Description page of Project Settings.


#include "UAVehiclePlayerController.h"
#include "DrawDebugHelpers.h"
#include "Runtime/UMG/Public/Components/Widget.h"
#include "TankUnit.h"
#include "HostStation.h"
#include "controller_ui_widgetc.h"




int AUAVehiclePlayerController::ToggleMouseCursor()
{
  if (bShowMouseCursor == 1)
  {
    bShowMouseCursor = 0;
    // if pawn is a host station, disable spawn mode
    AHostStation* PawnHostStation = Cast<AHostStation>(GetPawn());
    if(PawnHostStation!=nullptr)
    {
      PawnHostStation->SpawnState=0;
      // hide spawn icon
      ControllerUIWidget->SpawnUnitsCursorCC->SetVisibility(ESlateVisibility::Hidden);
    }
    Set_Game_only();
  }
  else{
    bShowMouseCursor = 1;
    Set_UI_only();
  }

  return bShowMouseCursor;
}
void AUAVehiclePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

        // move pawn barrel towards screen
        int32 Width, Height;
        GetViewportSize(Width, Height);
        FVector Location, Rotation;
        DeprojectScreenPositionToWorld(Width*0.5, Height*0.5, Location, Rotation);
        ATankUnit* ControlledVehicle = Cast<ATankUnit>(GetPawn());
        if(ControlledVehicle != nullptr)
        {

          ControlledVehicle->AimTowards(Rotation);

          // if the cursor is shown, draw debug line
          if(bShowMouseCursor == 1)
          {
            //  APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

            // FVector MouseLocation, MouseDirection;
            // DeprojectMousePositionToWorld(MouseLocation, MouseDirection);

            // DrawDebugLine(
            //     GetWorld(),
            //     MouseLocation - FVector(0,0,100),
            //     MouseLocation+MouseDirection*(100000),
            //     FColor(255,0,0),
            //     true,
            //     1.,
            //     1,
            //     10
            //     );

          }


        }
}
void AUAVehiclePlayerController::SetUIForPawn(APawn* NewPawn, UWidget* SpawnUnitButton)
{
  // is it a tank?
  ATankUnit* NewPawnTank = Cast<ATankUnit>(NewPawn);

  // is is a HostStation
  AHostStation* NewPawnHostStation = Cast<AHostStation>(NewPawn);
  if(NewPawnHostStation!=nullptr)
  {
    SpawnUnitButton->SetVisibility(ESlateVisibility::Visible);
  }
  else
  {
    SpawnUnitButton->SetVisibility(ESlateVisibility::Hidden);
  }
}
void AUAVehiclePlayerController::HandleLeftMouseClick()
{
  // check if in ui mode
  if(Cast<AHostStation>(GetPawn())!=nullptr)
  {
    if(Cast<AHostStation>(GetPawn())->SpawnState)
    {
      Cast<AHostStation>(GetPawn())->HandleLeftMouseClick();
    }
    else if(UI_enabled)
    {
      UE_LOG(LogTemp, Warning, TEXT("Click Map Location"));
    }
  }
  else if(Cast<ATankUnit>(GetPawn())!=nullptr)
  {
    if(UI_enabled)
    {
      UE_LOG(LogTemp, Warning, TEXT("Click Map Location"));
    }
    else
    {
      Cast<ATankUnit>(GetPawn())->HandleLeftMouseClick();
    }
  }

}
