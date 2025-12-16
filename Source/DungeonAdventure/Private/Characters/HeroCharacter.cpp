// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HeroCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "PaperZDAnimInstance.h"
#include "Characters/EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/BaseHUD.h"
#include "Widgets/HeartContainerComponent.h"

AHeroCharacter::AHeroCharacter()
{

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 150.f;


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(RootComponent);

}

void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHeroCharacter::Movement);
		Input->BindAction(AttackAction, ETriggerEvent::Started, this, &AHeroCharacter::Attack);
	}
}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	AddDefaultInputMapping();
	InitializeHUD();
}

void AHeroCharacter::OnHitAnimationEnd(bool bCompleted)
{
	Super::OnHitAnimationEnd(bCompleted);

	HitStop();
}

void AHeroCharacter::DecreaseHealth(const float IncomingDamage)
{
	Super::DecreaseHealth(IncomingDamage);

	if (HUDWidget && HUDWidget->HeartBox)
	{
		HUDWidget->HeartBox->UpdateCurrentHealth(GetCurrentHealth());
	}
}

void AHeroCharacter::Movement(const FInputActionValue& Value)
{
	if (!IsStunned() && IsAlive() && !IsAttacking()) {
	
		Directionality = Value.Get<FVector2D>();
	
		AddMovementInput(FVector(1.f, 0.f, 0.f), Directionality.X);
		AddMovementInput(FVector(0.f, 1.f, 0.f), Directionality.Y);

	}
}

void AHeroCharacter::Attack(const FInputActionValue& Value)
{
	if (!IsStunned() && IsAlive() && !IsAttacking()) {
		Attacking = true;

		FZDOnAnimationOverrideEndSignature OnOverrideEnd;
		OnOverrideEnd.BindUObject(this, &AHeroCharacter::OnAttackAnimationEnd);

		GetAnimInstance()->PlayAnimationOverride(AttackSequence, "DefaultSlot", 1.5f, 0.f, OnOverrideEnd);
	}
}

void AHeroCharacter::CheckHit()
{
	TArray<AActor*> OverlappingActors;
	HitBox->GetOverlappingActors(OverlappingActors, AEnemyBase::StaticClass());

	for (AActor* Actor : ReverseIterate(OverlappingActors))
	{
		if (Actor)
		{
			UGameplayStatics::ApplyDamage(Actor, 10.f,
				GetController(),
				this, UDamageType::StaticClass());
		}
	}

}



void AHeroCharacter::AddDefaultInputMapping()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
	
		if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->GetLocalPlayer()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->AddMappingContext(InputContext, 0);
			}
		}
	}
}

void AHeroCharacter::OnAttackAnimationEnd(bool bCompleted)
{
	Attacking = false;
}

void AHeroCharacter::InitializeHUD()
{
	if (!HUDWidgetClass)
	{
		return;
	}

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		HUDWidget = CreateWidget<UBaseHUD>(PlayerController, HUDWidgetClass);

		if (HUDWidgetClass)
		{
			HUDWidget->AddToViewport();
			if (HUDWidget->HeartBox && HealthComponent)
			{
				HUDWidget->HeartBox->InitHeartPieces(GetMaxHealth());
			}
		}
	}
}


