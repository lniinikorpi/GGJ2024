// Fill out your copyright notice in the Description page of Project Settings.


#include "GGameModeBase.h"

#include "AI/GAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"

AGGameModeBase::AGGameModeBase()
{
	SpawnInterval = 5;
	EnemiesLeft = 9;
}

void AGGameModeBase::StartPlay()
{
	Super::StartPlay();
	GetWorldTimerManager().SetTimer(SpawnEnemiesTimerHandle, this, &AGGameModeBase::SpawnEnemies_TimeElapsed, SpawnInterval, false);
}

void AGGameModeBase::OnActorKilled(AActor* VictimActor, AActor* KillerActor)
{
	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(KillerActor));
	if (VictimActor->GetClass()->IsChildOf(AGAICharacter::StaticClass()))
	{
		EnemiesLeft -= 1;
		UE_LOG(LogTemp, Warning, TEXT("Enemies left: %d"), EnemiesLeft);
		if(EnemiesLeft <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("You winned!"));
		}
	}
}

void AGGameModeBase::SpawnEnemies_TimeElapsed()
{
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnQuery, this, EEnvQueryRunMode::AllMatching, nullptr);

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
	for (int i = 0; i < 10; ++i)
	{

		UE_LOG(LogTemp, Warning, TEXT("Enemies left: %d"), i);
		FVector Location = Locations[FMath::RandRange(0, Locations.Num() - 1)];
		Location.Z = 120;
		TSubclassOf<AActor> Enemy = EnemyClasses[FMath::RandRange(0, EnemyClasses.Num() - 1)];
		GetWorld()->SpawnActor<AActor>(Enemy, Location, FRotator::ZeroRotator);
		Locations.Remove(Location);
	}
}
