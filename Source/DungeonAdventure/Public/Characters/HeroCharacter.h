// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "HeroCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;
class UBoxComponent;
class UPaperZDAnimSequence;
class UBaseHUD;
class AProjectileBase;

UCLASS()
class DUNGEONADVENTURE_API AHeroCharacter : public ABaseCharacter
{
	GENERATED_BODY()


public:
	AHeroCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void CheckHit();

	UFUNCTION(BlueprintCallable)
	void FireArrow();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement)
	FVector2D Directionality;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* InputContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* BowAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* AttackSequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* BowSequence;

	UPROPERTY(EditDefaultsOnly, Category=UI)
	TSubclassOf<UBaseHUD> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category=Projectile)
	TSubclassOf<AProjectileBase> ArrowClass;

	UPROPERTY(EditAnywhere, Category=Combat)
	float SwordDamage;

	UFUNCTION()
	void Movement(const FInputActionValue& Value);

	UFUNCTION()
	void Attack(const FInputActionValue& Value);

	bool CanAct();

	UFUNCTION()
	void ShootBow(const FInputActionValue& Value);

	void BeginPlay() override;
	FORCEINLINE bool IsAttacking() const { return Attacking; }

	void OnHitAnimationEnd(bool bCompleted) override;
	void DecreaseHealth(const float IncomingDamage) override;
	
private:

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* HitBox;

	UPROPERTY()
	UBaseHUD* HUDWidget;


	void AddDefaultInputMapping();
	void OnAttackAnimationEnd(bool bCompleted);

	bool Attacking;
	void InitializeHUD();
	
};
