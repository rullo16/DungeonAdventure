// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UBaseHUD;

UCLASS()
class DUNGEONADVENTURE_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="HUD")
	TSubclassOf<UBaseHUD> HUDWidgetClass;

	UPROPERTY()
	UBaseHUD* HUDWidget;

public:
	FORCEINLINE UBaseHUD* GetHUDWidget() const { return HUDWidget; }
};
