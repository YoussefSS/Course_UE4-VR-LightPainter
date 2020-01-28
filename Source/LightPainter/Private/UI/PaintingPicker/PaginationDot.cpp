// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/UI/PaintingPicker/PaginationDot.h"

void UPaginationDot::SetActive(bool Active)
{
	DotImage->SetOpacity(Active ? 1 : DisabledOpacity);
}
