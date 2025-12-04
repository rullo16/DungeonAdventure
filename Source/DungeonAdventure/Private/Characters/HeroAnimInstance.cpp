// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HeroAnimInstance.h"
#include "Characters/HeroCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UHeroAnimInstance::OnInit_Implementation()
{

	Super::OnInit_Implementation();

	HeroCharacter = Cast<AHeroCharacter>(GetOwningActor());
	if (HeroCharacter)
	{
		HeroCharacterMovement = HeroCharacter->GetCharacterMovement();
	}
}

void UHeroAnimInstance::OnTick_Implementation(float DeltaTime)
{
	Super::OnTick_Implementation(DeltaTime);
	if (HeroCharacterMovement)
	{
		Velocity = UKismetMathLibrary::VSizeXY(HeroCharacterMovement->Velocity);
	}
}
