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
	AddMovementInput(Direction);
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
		UE_LOG(LogTemp, Warning, TEXT("Overlapping with player"));

		AController* DamageInstigator = GetController();

		UGameplayStatics::ApplyDamage(OverlappingPlayer, 10.f, 
			DamageInstigator, 
			this, UDamageType::StaticClass());
	}
}
