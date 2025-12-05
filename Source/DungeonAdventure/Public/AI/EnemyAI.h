// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAI.generated.h"

class APawn;
class AEnemyBase;

UCLASS()
class DUNGEONADVENTURE_API AEnemyAI : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAI();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;


private:

	UPROPERTY()
	APawn* TargetPlayer;
	
	UPROPERTY()
	AEnemyBase* PossessedPawn;

	void FindTargetPlayer();
};
