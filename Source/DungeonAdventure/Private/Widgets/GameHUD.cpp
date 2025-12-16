// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/GameHUD.h"
#include "Widgets/BaseHUD.h"

void AGameHUD::BeginPlay()
{

	Super::BeginPlay();

	UWorld* World = GetWorld();

	if (!World) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!PlayerController && !HUDWidgetClass) return;
	HUDWidget = CreateWidget<UBaseHUD>(PlayerController, HUDWidgetClass);

	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}

}
