// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/GAction.h"
#include "GAction_Attack.generated.h"

class AGProjectile_Base;
/**
 * 
 */
UCLASS()
class GGJ2024_API UGAction_Attack : public UGAction
{
	GENERATED_BODY()
	UGAction_Attack();

public:
	virtual void StartAction_Implementation(AActor* Instigator) override;

protected:
	UFUNCTION()
	void ActionAttackTimeElapsed(ACharacter* Instigator);
	FTransform CalculateProjectileTransform(ACharacter* InstigatorActor);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	float AttackDelay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	float FireRateDelay;

	UFUNCTION()
	void FireRateTimeElapsed(ACharacter* Instigator);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	float SpawnDelay;
	UFUNCTION()
	void SpawnDelayTimeElapsed(ACharacter* Instigator);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USoundBase> StartSound;
};
