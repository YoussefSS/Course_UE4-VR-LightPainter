// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "Engine/World.h"
#include "Public/Saving/PainterSaveGame.h"
#include "Components\InputComponent.h"
#include "Public\PaintingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"

AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);
}

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	UPainterSaveGame* Painting = UPainterSaveGame::Create();
	if (Painting && Painting->Save())
	{
		CurrentSlotName = Painting->GetSlotName();
	}
	
	if (PaintBrushHandControllerClass)
	{
		RightPaintBrushHandController = GetWorld()->SpawnActor<AHandControllerBase>(PaintBrushHandControllerClass);
		RightPaintBrushHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightPaintBrushHandController->SetOwner(this);
	}
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Released, this, &AVRPawn::RightTriggerReleased);

	PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Released, this, &AVRPawn::Save);
}

void AVRPawn::Save()
{
	auto GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	GameMode->Save();
	UStereoLayerFunctionLibrary::ShowSplashScreen();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu")); 
}

