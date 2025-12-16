// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyBase.h"
#include "AIController.h"
#include "Components/BoxComponent.h"
#include "Interfaces/OverlapInterface.h"
#include "Characters/HeroCharacter.h"
#include "Kismet/GameplayStatics.h"

AEnemyBase::AEnemyBase()
{
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	HurtBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlapBegin);

}

void AEnemyBase::WalkTowards(const FVector& Direction)
{
	if (IsAlive() && !IsStunned())
	{
		AddMovementInput(Direction);
	}
}

void AEnemyBase::SetOverlappingPlayer(AHeroCharacter* Hero)
{
	OverlappingPlayer = Hero;
}

//void AEnemyBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	IOverlapInterface* OverlapInterface = Cast<IOverlapInterface>(OtherActor);
//	if (OverlapInterface)
//	{
//		AHeroCharacter* Player = Cast<AHeroCharacter>(OtherActor);
//		if (Player) {
//			OverlapInterface->SetOverlappingPlayer(Player);
//		}
//	}
//}


void AEnemyBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//OverlappingPlayer = Cast<AHeroCharacter>(OtherActor);
	AHeroCharacter* Player = Cast<AHeroCharacter>(OtherActor);
	if (Player) {
		OverlappingPlayer = Player;

		if (OtherComp == OverlappingPlayer->GetHurtBox() && !Player->IsInvincible())
		{

			AController* DamageInstigator = GetController();

			UGameplayStatics::ApplyDamage(OverlappingPlayer, 10.f, 
				DamageInstigator, 
				this, UDamageType::StaticClass());
		}
	}
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	SetStunned(true);
	GetWorldTimerManager().SetTimer(
		StunnedTimerHandle,
		this,
		&AEnemyBase::EndStunned,
		0.5f,
		false
	);
	HitStop();

	if(!IsAlive())
	{
		DeathSpawnVFX();
		Destroy();
	}

	return Damage;
}

void AEnemyBase::EndStunned()
{
	SetStunned(false);
}

void AEnemyBase::DeathSpawnVFX()
{
	if(DeathVFX)
	{ 
	
		GetWorld()->SpawnActor<AActor>(DeathVFX, GetActorLocation(), FRotator::ZeroRotator);
		
	}
}
