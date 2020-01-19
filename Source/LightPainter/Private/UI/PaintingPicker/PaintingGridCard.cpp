// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/UI/PaintingPicker/PaintingGridCard.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet\StereoLayerFunctionLibrary.h"

void UPaintingGridCard::SetPaintingName(FString NewPaintingName)
{
	PaintingName = NewPaintingName;
	SlotName->SetText(FText::FromString(PaintingName));

	CardButton->OnClicked.AddDynamic(this, &UPaintingGridCard::CardButtonClicked);
}

void UPaintingGridCard::CardButtonClicked()
{
	UStereoLayerFunctionLibrary::ShowSplashScreen(); // Just following along the lecs, this is incase it takes a long time to load into the level, we then need to hide it

	//TODO: Refactor out magic string
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Canvas"), true, "SlotName=" + PaintingName); // the slotname + bit is passing state between levels
}
