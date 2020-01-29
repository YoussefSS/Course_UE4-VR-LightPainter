// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/UniformGridPanel.h"
#include "PaintingGridCard.h"
#include "Components/HorizontalBox.h"
#include "Public/UI/PaintingPicker/PaginationDot.h"

#include "PaintingGrid.generated.h"

/**
 * 
 */
UCLASS()
class LIGHTPAINTER_API UPaintingGrid : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void AddPainting(int32 PaintingIndex, FString PaintingName);

	// API for adding a pagination dot
	void AddPaginationDot(bool Active);


	void ClearPaintings();
	void ClearPaginationDots();

	int32 GetNumberOfSlots() const;
protected:

	// Binds a component in the UI heirarchy with the name Painting Grid
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UUniformGridPanel* PaintingGrid;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
	UHorizontalBox* PaginationDots;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaintingGridCard> GridCardClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPaginationDot> PaginationDotClass;

	UPROPERTY(EditDefaultsOnly)
	float PaginationDotPadding = 8;
};
