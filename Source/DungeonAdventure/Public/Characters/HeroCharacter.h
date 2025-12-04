// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "HeroCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class DUNGEONADVENTURE_API AHeroCharacter : public ABaseCharacter
{
	GENERATED_BODY()


public:
	AHeroCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement)
	FVector2D Directionality;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* InputContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	UFUNCTION()
	void Movement(const FInputActionValue& Value);


private:

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	void AddDefaultInputMapping();

	
};
