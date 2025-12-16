// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "EnemyBase.generated.h"

class AAIController;
class AHeroCharacter;

UCLASS()
class DUNGEONADVENTURE_API AEnemyBase : public ABaseCharacter
{
	GENERATED_BODY()


public:
	AEnemyBase();
	
	UFUNCTION(BlueprintCallable, Category= Movement)
	void WalkTowards(const FVector& Direction);

	virtual void SetOverlappingPlayer(class AHeroCharacter* Hero);
protected:
	UPROPERTY(EditDefaultsOnly, Category=VFX)
	TSubclassOf<AActor> DeathVFX;

	void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	void EndStunned();
	void DeathSpawnVFX();
private:
	FTimerHandle StunnedTimerHandle;
	AHeroCharacter* OverlappingPlayer;
	
};
