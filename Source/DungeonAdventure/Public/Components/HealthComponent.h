// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEONADVENTURE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth() const { return CurrentHealth; }
protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "Actor Attributes")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actor Attributes")
	float CurrentHealth;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void DecreaseHealth(const float IncomingDamage);
	bool IsAlive();
		
};
