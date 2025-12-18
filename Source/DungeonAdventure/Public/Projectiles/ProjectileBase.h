// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UPaperSpriteComponent;
class ABaseCharacter;

UCLASS()
class DUNGEONADVENTURE_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:

	UPROPERTY(EditAnywhere, Category = Damage)
	float Damage;

	TSubclassOf<ABaseCharacter> OverlappingActor;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category=Movement)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, Category=Sprite)
	UPaperSpriteComponent* ProjectileSprite;

	

};
