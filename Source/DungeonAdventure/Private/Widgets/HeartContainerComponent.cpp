// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HeartContainerComponent.h"
#include "Widgets/HeartContainer.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"

void UHeartContainerComponent::InitHeartPieces(float MaxHealth)
{
	if (!HeartContainer || !HeartWidget) return;

	Hearts.Empty();
	

	for (int i = 0; i < MaxHealth; i++)
	{
		if (i % 10 != 0) continue;
		UHeartContainer* NewHeart = CreateWidget<UHeartContainer>(this, HeartWidget);
		if (NewHeart)
		{
			HeartContainer->AddChild(NewHeart);
			Hearts.Add(NewHeart);
		}
	}
}

void UHeartContainerComponent::UpdateCurrentHealth(float CurrentHealth)
{
	for (int i = 0; i < Hearts.Num(); i++)
	{
		if (Hearts[i])
		{
			bool bIsFull = (i < (CurrentHealth / 10));
			Hearts[i]->SetHeartImage(bIsFull);
		}
	}
} 
