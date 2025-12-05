// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

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
	

}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("DamageTaken: %f"), DamageAmount);
	//Destroy();
	return DamageAmount;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();


}
