// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "BaseCharacter.generated.h"

class UBoxComponent;

UCLASS()
class DUNGEONADVENTURE_API ABaseCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:

	ABaseCharacter();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* HurtBox;

	void BeginPlay() override;

private:

};
