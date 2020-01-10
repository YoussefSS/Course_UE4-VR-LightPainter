// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/HandController.h"
#include "Engine/World.h"

AHandController::AHandController()
{
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(MotionController);
	MotionController->SetTrackingSource(EControllerHand::Right);
	MotionController->SetShowDeviceModel(true);
}

void AHandController::TriggerPressed()
{
	AStroke* Stroke = GetWorld()->SpawnActor<AStroke>(StrokeClass);
	Stroke->SetActorLocation(GetActorLocation());
}

void AHandController::TriggerReleased()
{

}

void AHandController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

