// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/HealthComponent.h"
#include "PaperZDAnimInstance.h"
#include "AsyncRootMovement.h"
#include "PaperFlipbookComponent.h"

ABaseCharacter::ABaseCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, -10000.f, 0.f);

	HurtBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HurtBox"));
	HurtBox->SetupAttachment(RootComponent);
	HurtBox->SetBoxExtent(FVector(20.f, 20.f, 70.f));
	HurtBox->SetGenerateOverlapEvents(true);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Attributes"));

}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	DecreaseHealth(DamageAmount);
	Stunned = true;

	FZDOnAnimationOverrideEndSignature OnOverrideEnd;
	OnOverrideEnd.BindUObject(this, &ABaseCharacter::OnHitAnimationEnd);

	GetAnimInstance()->PlayAnimationOverride(HitSequence, "DefaultSlot", 1.f, 0.f,OnOverrideEnd);
	GetKnockedBack(this->GetActorLocation(), DamageCauser->GetActorLocation());
	StartInvincibility(1.f);
	FlashSprite();
	
	if (!IsAlive())
	{
		GetAnimInstance()->JumpToNode("DeathJump");
		GetCharacterMovement()->DisableMovement();
	}

	return DamageAmount;
}

float ABaseCharacter::GetCurrentHealth()
{
	return HealthComponent->GetCurrentHealth();
}

float ABaseCharacter::GetMaxHealth()
{
	return HealthComponent->GetMaxHealth();
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::DecreaseHealth(const float IncomingDamage)
{
	if (HealthComponent && IsAlive())
	{
		HealthComponent->DecreaseHealth(IncomingDamage);
	}
}

bool ABaseCharacter::IsAlive()
{
	return HealthComponent && HealthComponent->IsAlive();
}

void ABaseCharacter::OnHitAnimationEnd(bool bCompleted)
{
	Stunned = false;
}

void ABaseCharacter::GetKnockedBack(const FVector& CharacterLocation, const FVector& DamageCauseLocation)
{
	FVector Direction = (CharacterLocation - DamageCauseLocation).GetSafeNormal();

	UAsyncRootMovement* Knockback = UAsyncRootMovement::AsyncRootMovement  (
		this,
		GetCharacterMovement(),
		Direction,
		250.f,
		1.f,                         
		false,
		nullptr,
		ERootMotionFinishVelocityMode::MaintainLastRootMotionVelocity,
		FVector::ZeroVector,
		0.f,
		false
	);

	if (Knockback)
	{
		Knockback->Activate();
	}
}

void ABaseCharacter::FlashSprite()
{
	GetSprite()->SetSpriteColor(FLinearColor::Red);

	GetWorldTimerManager().SetTimer(
		FlashTimerHandle,
		this,
		&ABaseCharacter::ResetSpriteColor,
		0.1f,
		false
	);
}

void ABaseCharacter::ResetSpriteColor()
{
	GetSprite()->SetSpriteColor(FLinearColor::White);
}

void ABaseCharacter::HitStop()
{
	CustomTimeDilation = 0.f;
	GetWorldTimerManager().SetTimer(
		HitStopTimerHandle,
		this,
		&ABaseCharacter::ResetTimeDilation,
		0.1f,
		false
	);
}

void ABaseCharacter::ResetTimeDilation()
{
	CustomTimeDilation = 1.f;
}

void ABaseCharacter::StartInvincibility(float Duration)
{
	bIsInvincible = true;
	bFlickerVisible = true;

	GetWorldTimerManager().SetTimer(
		FlickerTimerHandle,
		this,
		&ABaseCharacter::FlickerTick,
		0.1f,
		true
	);

	GetWorldTimerManager().SetTimer(
		InvincibilityTimerHandle,
		this,
		&ABaseCharacter::EndInvincibility,
		Duration,
		false
	);
}

void ABaseCharacter::EndInvincibility()
{
	bIsInvincible = false;

	GetWorldTimerManager().ClearTimer(FlickerTimerHandle);
	GetSprite()->SetVisibility(true);
	GetSprite()->SetSpriteColor(FLinearColor::White);

}

void ABaseCharacter::FlickerTick()
{
	bFlickerVisible = !bFlickerVisible;

	float Alpha = bFlickerVisible ? 1.f : 0.3f;
	GetSprite()->SetSpriteColor(FLinearColor(1.f, 1.f, 1.f, Alpha));
}





