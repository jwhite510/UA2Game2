// Fill out your copyright notice in the Description page of Project Settings.


#include "UAVehiclePlayerController.h"
#include "DrawDebugHelpers.h"
#include "TankUnit.h"




int AUAVehiclePlayerController::ToggleMouseCursor()
{

  if (bShowMouseCursor == 1)
  {
    bShowMouseCursor = 0;
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
