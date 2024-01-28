// Fill out your copyright notice in the Description page of Project Settings.


#include "GGameModeBase.h"

#include "Action/GActionComponent.h"
#include "AI/GAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "Kismet/GameplayStatics.h"

AGGameModeBase::AGGameModeBase()
{
	SpawnInterval = .1;
	EnemySpawnInterval = 5;
	MaxEnemiesCount = 7;
	CurrentEnemiesCount = 0;
}

void AGGameModeBase::StartPlay()
{
	Super::StartPlay();
	GetWorldTimerManager().SetTimer(SpawnHumansTimerHandle, this, &AGGameModeBase::SpawnHumans_TimeElapsed, SpawnInterval, false);
	GetWorldTimerManager().SetTimer(SpawnEnemiesTimerHandle, this, &AGGameModeBase::SpawnEnemies_TimeElapsed, EnemySpawnInterval, true);
}

void AGGameModeBase::OnActorKilled(AActor* VictimActor, AActor* KillerActor)
{
	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(KillerActor));
	if (VictimActor->GetClass()->IsChildOf(AGAICharacter::StaticClass()))
	{
		UGActionComponent* ActionComp = VictimActor->GetComponentByClass<UGActionComponent>();
		if(!ActionComp)
		{
			return;
		}
		if (!ActionComp->ActiveGameplayTags.HasTag(HumanTag))
		{
			CurrentEnemiesCount--;
			return;
		}
		HumansLeft -= 1;
		OnHumanPooped.Broadcast(HumansLeft, 10);
		UE_LOG(LogTemp, Warning, TEXT("Enemies left: %d"), HumansLeft);
		if(HumansLeft <= 0)
		{
			if (IsGameEnd)
			{
				return;
			}
			IsGameEnd = true;
			UE_LOG(LogTemp, Warning, TEXT("You winned!"));
			OnGameEnd.Broadcast(true);
		}
	}
	else
	{
		if(IsGameEnd)
		{
			return;
		}
		IsGameEnd = true;
		OnGameEnd.Broadcast(false);
	}
}

void AGGameModeBase::SpawnHumans_TimeElapsed()
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
		HumansLeft += 1;
		UE_LOG(LogTemp, Warning, TEXT("Enemies left: %d"), i);
		FVector Location = Locations[FMath::RandRange(0, Locations.Num() - 1)];
		Location.Z = 120;
		TSubclassOf<AActor> Enemy = HumanClasses[FMath::RandRange(0, HumanClasses.Num() - 1)];
		GetWorld()->SpawnActor<AActor>(Enemy, Location, FRotator::ZeroRotator);
		Locations.Remove(Location);
	}
}

void AGGameModeBase::SpawnEnemies_TimeElapsed()
{
	if (CurrentEnemiesCount >= MaxEnemiesCount)
	{
		return;
	}
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnEnemyQuery, this, EEnvQueryRunMode::RandomBest25Pct, nullptr);

	if (!QueryInstance)
	{
		return;
	}
	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AGGameModeBase::OnEnemySpawnQueryCompleted);
}

void AGGameModeBase::OnEnemySpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
	EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		return;
	}
	TArray<FVector> Locations;

	if (QueryInstance->GetQueryResultsAsLocations(Locations) == 0)
	{
		return;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Enemies left: %d"), i);
	FVector Location = Locations[0];
	Location.Z = 120;
	TSubclassOf<AActor> Enemy = EnemyClasses[FMath::RandRange(0, EnemyClasses.Num() - 1)];
	GetWorld()->SpawnActor<AActor>(Enemy, Location, FRotator::ZeroRotator);
	Locations.Remove(Location);
	CurrentEnemiesCount++;
}
