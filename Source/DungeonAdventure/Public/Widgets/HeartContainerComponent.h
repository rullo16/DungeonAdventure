// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeartContainerComponent.generated.h"

class UHorizontalBox;
class UHeartContainer;
class UTexture2D;

UCLASS()
class DUNGEONADVENTURE_API UHeartContainerComponent : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	void InitHeartPieces(float MaxHealth);
	void UpdateCurrentHealth(float CurrentHealth);
	

protected:

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* HeartContainer;

	UPROPERTY(EditDefaultsOnly, Category=Heart)
	TSubclassOf<UHeartContainer> HeartWidget;

private:
	UPROPERTY()
	TArray<UHeartContainer*> Hearts;
};
