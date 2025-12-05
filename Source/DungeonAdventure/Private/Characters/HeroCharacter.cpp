// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HeroCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"

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
	}
}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	AddDefaultInputMapping();
}

void AHeroCharacter::Movement(const FInputActionValue& Value)
{
	
	Directionality = Value.Get<FVector2D>();
	
	AddMovementInput(FVector(1.f, 0.f, 0.f), Directionality.X);
	AddMovementInput(FVector(0.f, 1.f, 0.f), Directionality.Y);
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
