// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "GameFramework/GameModeBase.h"
#include "GGameModeBase.generated.h"

class UEnvQuery;
/**
 * 
 */
UCLASS()
class GGJ2024_API AGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGGameModeBase();

	virtual void StartPlay() override;
	virtual void OnActorKilled(AActor* VictimActor, AActor* KillerActor);

protected:
	UPROPERTY(EditDefaultsOnly, Category="AI")
	float SpawnInterval;

	UPROPERTY(EditAnywhere, Category = "AI")
	TSubclassOf<AActor> MeleeEnemyClass;
	UPROPERTY(EditDefaultsOnly, Category = "AI");
	FTimerHandle SpawnEnemiesTimerHandle;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UEnvQuery> SpawnQuery;

	UFUNCTION()
	void SpawnEnemies_TimeElapsed();
	UFUNCTION()
	void OnSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);
};
