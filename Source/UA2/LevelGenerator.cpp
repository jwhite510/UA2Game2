// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGenerator.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/LevelStreaming.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"

void ALevelGenerator::BeginPlay()
{
  Super::BeginPlay();
  UE_LOG(LogTemp, Warning, TEXT("ALevelGenerator BeginPlay called"));

  ULevelStreaming* LevelStreaming;
  ULevelStreaming* LevelStreaming2;
  // list of level names
  TArray<FName> StreamingLevelNames;

  StreamingLevelNames.Add(FName("Procedural01"));
  StreamingLevelNames.Add(FName("Procedural02"));

  for(int32 i=0;i<LevelGridSize;i++){
    UE_LOG(LogTemp, Warning, TEXT("i:%i"), i);
    for(int32 j=0;j<LevelGridSize;j++){
      UE_LOG(LogTemp, Warning, TEXT("j:%i"), j);

      FString UniqueName = "Procedural_";
      UniqueName.AppendInt(i);
      UniqueName.AppendInt(j);
      UE_LOG(LogTemp, Warning, TEXT("UniqueName:%s"), *UniqueName);


      // streaming level names
      // select random name
      int32 RandomNum = UKismetMathLibrary::RandomInteger(StreamingLevelNames.Num());
      LevelStreaming = UGameplayStatics::GetStreamingLevel(GetWorld(), StreamingLevelNames[RandomNum]);
      LevelStreaming2 = LevelStreaming->CreateInstance(UniqueName);

      // set level transform
      LevelStreaming2->SetShouldBeLoaded(1);
      LevelStreaming2->SetShouldBeVisible(1);

      float TileSize = 2100;

      float j_t = j * TileSize;
      float i_t = i * TileSize;

      i_t -= (LevelGridSize * TileSize) / 2;
      j_t -= (LevelGridSize * TileSize) / 2;

      FTransform Trans = UKismetMathLibrary::MakeTransform(
          FVector(i_t, j_t, 0),
          FRotator(0,0,0),
          FVector(0, 0, 0)
          );

      // level transform
      LevelStreaming2->LevelTransform = Trans;

    }
  }

}
