// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/BaseCharacter.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	CollisionComponent->SetGenerateOverlapEvents(true);
	RootComponent = CollisionComponent;

	ProjectileSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Projectile Sprite"));
	ProjectileSprite->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->SetUpdatedComponent(CollisionComponent);
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->InitialSpeed = 200.f;
	ProjectileMovement->MaxSpeed = 200.f;

}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnOverlapBegin);
}

void AProjectileBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner())
	{
		AController* DamageInstigator = GetOwner()->GetInstigatorController();
		UGameplayStatics::ApplyDamage(OtherActor, Damage, DamageInstigator, this, UDamageType::StaticClass());
		UE_LOG(LogTemp, Warning, TEXT("Projectile hit %s"), *OtherActor->GetName());
		Destroy();
	}
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

