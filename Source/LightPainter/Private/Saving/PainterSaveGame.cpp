// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Saving/PainterSaveGame.h"
#include "Kismet\GameplayStatics.h"
#include "GameFramework\SaveGame.h"
#include "EngineUtils.h"
#include "Public/Stroke.h"

UPainterSaveGame* UPainterSaveGame::Create()
{
	USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(StaticClass());
	return Cast<UPainterSaveGame>(NewSaveGame);
}

bool UPainterSaveGame::Save()
{
	return UGameplayStatics::SaveGameToSlot(this, TEXT("Test"), 0);
}

UPainterSaveGame* UPainterSaveGame::Load()
{
	 return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Test"), 0));
}

void UPainterSaveGame::SerializeFromWorld(UWorld* World)
{

	Strokes.Empty();
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		Strokes.Add(StrokeItr->GetClass());
		// TODO: Serialize
	}
}

void UPainterSaveGame::DeserializeToWorld(UWorld* World)
{
	ClearWorld(World);
	for (TSubclassOf<class AStroke> StrokeClass : Strokes)
	{
		World->SpawnActor<AStroke>(StrokeClass);
	}
	// Spawn stroke of that type

	
}

void UPainterSaveGame::ClearWorld(UWorld* World)
{
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		StrokeItr->Destroy();
		// TODO: Serialize
	}
}
