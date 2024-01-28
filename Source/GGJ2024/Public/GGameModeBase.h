// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "GameFramework/GameModeBase.h"
#include "GGameModeBase.generated.h"

class UEnvQuery;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameEnd, bool, PlayerWon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHumanPooped, int32, CurrentPooped, int32, MaxPooped);

UCLASS()
class GGJ2024_API AGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGGameModeBase();

	virtual void StartPlay() override;
	virtual void OnActorKilled(AActor* VictimActor, AActor* KillerActor);
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag HumanTag;

	UPROPERTY(BlueprintAssignable)
	FOnGameEnd OnGameEnd;
	UPROPERTY(BlueprintAssignable)
	FOnHumanPooped OnHumanPooped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsGameEnd;

protected:
	UPROPERTY(EditDefaultsOnly, Category="AI")
	float SpawnInterval;

	UPROPERTY(EditAnywhere, Category = "AI")
	TArray<TSubclassOf<AActor>> EnemyClasses;
	UPROPERTY(EditAnywhere, Category = "AI")
	TArray<TSubclassOf<AActor>> HumanClasses;
	UPROPERTY(EditDefaultsOnly, Category = "AI");
	FTimerHandle SpawnHumansTimerHandle;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UEnvQuery> SpawnQuery;


	int32 HumansLeft;

	UFUNCTION()
	void SpawnHumans_TimeElapsed();
	UFUNCTION()
	void OnSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UPROPERTY(EditDefaultsOnly, Category="AI")
	float EnemySpawnInterval;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	int32 MaxEnemiesCount;
	int32 CurrentEnemiesCount;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UEnvQuery> SpawnEnemyQuery;

	FTimerHandle SpawnEnemiesTimerHandle;
	UFUNCTION()
	void SpawnEnemies_TimeElapsed();
	UFUNCTION()
	void OnEnemySpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

};
