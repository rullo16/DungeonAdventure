// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PickupBow.h"
#include "Characters/HeroCharacter.h"

void APickupBow::HandlePickup(AHeroCharacter* Character)
{
	Super::HandlePickup(Character);
	UE_LOG(LogTemp, Warning, TEXT("Picked up Bow"));
	Character->BowUses += 5.f;
	UE_LOG(LogTemp, Warning, TEXT("Bow Uses: %f"), Character->BowUses);
}
