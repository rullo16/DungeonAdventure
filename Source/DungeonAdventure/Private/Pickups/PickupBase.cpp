// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/PickupBase.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "Characters/HeroCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	CollisionComponent->SetGenerateOverlapEvents(true);
	RootComponent = CollisionComponent;

	PickupSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Pickup Sprite"));
	PickupSprite->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnOverlapBegin);
}

void APickupBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHeroCharacter* Character = Cast<AHeroCharacter>(OtherActor);

	if (Character)
	{
		if (PickupSound)
		{
			UGameplayStatics::PlaySound2D(this, PickupSound);
		}
		HandlePickup(Character);
	}
}

void APickupBase::HandlePickup(AHeroCharacter* Character)
{
	Destroy();
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

