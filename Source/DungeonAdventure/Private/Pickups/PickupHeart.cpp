// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PickupHeart.h"
#include "Characters/HeroCharacter.h"

void APickupHeart::HandlePickup(AHeroCharacter* Character)
{
	Super::HandlePickup(Character);
	if (Character)
	{
		Character->IncreaseHealth(10.f);
	}
}
