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

	void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	AHeroCharacter* OverlappingPlayer;
	
};
