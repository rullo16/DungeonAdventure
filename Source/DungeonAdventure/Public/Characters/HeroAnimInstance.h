// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDAnimInstance.h"
#include "HeroAnimInstance.generated.h"

class AHeroCharacter;
class UCharacterMovementComponent;

UCLASS()
class DUNGEONADVENTURE_API UHeroAnimInstance : public UPaperZDAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void OnInit_Implementation() override;
	virtual void OnTick_Implementation(float DeltaTime) override;


	UPROPERTY(BlueprintReadOnly)
	AHeroCharacter* HeroCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UCharacterMovementComponent* HeroCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float Velocity;



};
