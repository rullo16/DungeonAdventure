// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnemyAI.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/EnemyBase.h"


AEnemyAI::AEnemyAI()
{
}

void AEnemyAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!TargetPlayer || !PossessedPawn) return;

		const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(PossessedPawn->GetActorLocation(), TargetPlayer->GetActorLocation());
		const FVector MoveDirection = UKismetMathLibrary::GetForwardVector(LookAtRotation);
		const FVector Distance = TargetPlayer->GetActorLocation() - PossessedPawn->GetActorLocation();
		if (Distance.Size() <= 10.f) return;
		PossessedPawn->WalkTowards(MoveDirection);
}

void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	
	FindTargetPlayer();
}

void AEnemyAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedPawn = Cast<AEnemyBase>(InPawn);

}

void AEnemyAI::FindTargetPlayer()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		TargetPlayer = PlayerController->GetPawn();
	}
}






