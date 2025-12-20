// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/PickupBase.h"
#include "PickupHeart.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONADVENTURE_API APickupHeart : public APickupBase
{
	GENERATED_BODY()
	
protected:
	void HandlePickup(class AHeroCharacter* Character) override;

};
