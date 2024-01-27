// Fill out your copyright notice in the Description page of Project Settings.


#include "GGameModeBase.h"

#include "EnvironmentQuery/EnvQueryManager.h"

AGGameModeBase::AGGameModeBase()
{
	SpawnInterval = 5;
}

void AGGameModeBase::StartPlay()
{
	Super::StartPlay();
	GetWorldTimerManager().SetTimer(SpawnEnemiesTimerHandle, this, &AGGameModeBase::SpawnEnemies_TimeElapsed, SpawnInterval, true);
}

void AGGameModeBase::OnActorKilled(AActor* VictimActor, AActor* KillerActor)
{
	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(KillerActor));
}

void AGGameModeBase::SpawnEnemies_TimeElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnQuery, this, EEnvQueryRunMode::RandomBest25Pct, nullptr);

	if (!QueryInstance)
	{
		return;
	}
	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AGGameModeBase::OnSpawnQueryCompleted);
}

void AGGameModeBase::OnSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Success)
	{
		return;
	}
	TArray<FVector> Locations;

	if (QueryInstance->GetQueryResultsAsLocations(Locations) == 0)
	{
		return;
	}
	Locations[0].Z = 120;
	GetWorld()->SpawnActor<AActor>(MeleeEnemyClass, Locations[0], FRotator::ZeroRotator);
}
