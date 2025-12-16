// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HeartContainer.h"
#include "Components/Image.h"

void UHeartContainer::SetHeartImage(bool bIsFull)
{

	if (HeartImage)
	{
		if (bIsFull)
		{
			HeartImage->SetBrushFromTexture(FullHeartTexture);
		}
		else
		{
			HeartImage->SetBrushFromTexture(EmptyHeartTexture);
		}
	}
}
