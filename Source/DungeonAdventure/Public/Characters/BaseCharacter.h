// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "BaseCharacter.generated.h"

class UBoxComponent;
class UHealthComponent;
class UPaperZDAnimSequence;
class USoundCue;

UCLASS()
class DUNGEONADVENTURE_API ABaseCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:

	ABaseCharacter();

	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	float GetCurrentHealth();
	float GetMaxHealth();

	FORCEINLINE bool IsStunned() const { return Stunned; }
	FORCEINLINE virtual void SetStunned(const bool bIsStunned) { Stunned = bIsStunned; }
	FORCEINLINE UBoxComponent* GetHurtBox() const { return HurtBox; }
	FORCEINLINE bool IsInvincible() const { return bIsInvincible; }
	
protected:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* HurtBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPaperZDAnimSequence* HitSequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundCue* HitSound;

	bool bIsInvincible;
	bool bFlickerVisible;

	FTimerHandle InvincibilityTimerHandle;
	FTimerHandle FlickerTimerHandle;

	void BeginPlay() override;
	
	virtual void DecreaseHealth(const float IncomingDamage);
	virtual bool IsAlive();
	UFUNCTION()
	virtual void OnHitAnimationEnd(bool bCompleted);
	UFUNCTION(BlueprintCallable)
	void GetKnockedBack(const FVector& CharacterLocation, const FVector& DamageCauseLocation);
	UFUNCTION(BlueprintCallable)
	void FlashSprite();
	void ResetSpriteColor();
	void HitStop();
	void ResetTimeDilation();
	void StartInvincibility(float Duration);
	void EndInvincibility();
	void FlickerTick();
private:
	bool Stunned;
	FTimerHandle FlashTimerHandle;
	FTimerHandle HitStopTimerHandle;

};
