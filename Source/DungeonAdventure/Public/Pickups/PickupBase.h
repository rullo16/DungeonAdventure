// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class UPaperSpriteComponent;
class UBoxComponent;
class USoundCue;

UCLASS()
class DUNGEONADVENTURE_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundCue* PickupSound;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual void HandlePickup(class AHeroCharacter* Character);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* PickupSprite;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionComponent;
};
