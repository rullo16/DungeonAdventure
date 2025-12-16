// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HeartContainer.generated.h"

class UTexture2D;

UCLASS()
class DUNGEONADVENTURE_API UHeartContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UImage* HeartImage;
	
	void SetHeartImage(bool bIsFull);

private:
	UPROPERTY(EditAnywhere, Category = "Heart Container")
	UTexture2D* FullHeartTexture;

	UPROPERTY(EditAnywhere, Category = "Heart Container")
	UTexture2D* EmptyHeartTexture;
};
