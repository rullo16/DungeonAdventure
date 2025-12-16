// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseHUD.generated.h"

class UHeartContainerComponent;

UCLASS()
class DUNGEONADVENTURE_API UBaseHUD : public UUserWidget
{
	GENERATED_BODY()



public:

	UPROPERTY(meta = (BindWidget))
	UHeartContainerComponent* HeartBox;
	
};
