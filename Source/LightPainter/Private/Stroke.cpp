// Fill out your copyright notice in the Description page of Project Settings.


#include "Stroke.h"
#include "Components/SplineMeshComponent.h"

AStroke::AStroke()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

void AStroke::Update(FVector CursorLocation)
{
	USplineMeshComponent* Spline = CreateSplineMesh();
	
	FVector StartPosition = GetActorTransform().InverseTransformPosition(CursorLocation); // InverseTransform transforms from world space to local space ..
	FVector EndPosition = GetActorTransform().InverseTransformPosition(PreviousCursorLocation); // .. can use Transform.TransformPoint to convert from local to world space
	Spline->SetStartAndEnd(StartPosition, FVector::ZeroVector, EndPosition, FVector::ZeroVector);

	PreviousCursorLocation = CursorLocation;
}

USplineMeshComponent* AStroke::CreateSplineMesh()
{
	USplineMeshComponent* NewSpline = NewObject<USplineMeshComponent>(this);
	NewSpline->SetMobility(EComponentMobility::Movable);
	NewSpline->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetIncludingScale);
	NewSpline->SetStaticMesh(SplineMesh);
	NewSpline->SetMaterial(0, SplineMaterial);
	NewSpline->RegisterComponent();

	return NewSpline;
}
