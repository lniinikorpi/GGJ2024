// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/GAction_Attack.h"

#include "GCharacter.h"
#include "Action/GActionComponent.h"
#include "AI/GAICharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

UGAction_Attack::UGAction_Attack()
{
	AttackDelay = .5f;
}

void UGAction_Attack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* Char = Cast<ACharacter>(Instigator);
	if (!Char)
	{
		return;
	}
	FTimerHandle TimerHandle;
	FTimerDelegate Delegate;
	Delegate.BindUFunction(this, "ActionAttackTimeElapsed", Char);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, AttackDelay, false);

	Instigator->GetComponentByClass<UGActionComponent>()->PlayPrimaryAttackEffect();
}

void UGAction_Attack::ActionAttackTimeElapsed(ACharacter* Instigator)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Instigator;
	GetWorld()->SpawnActor<AActor>(ProjectileClass, CalculateProjectileTransform(Instigator), SpawnParams);

	FTimerHandle TimerHandleFireRate;
	FTimerDelegate DelegateFireRate;
	DelegateFireRate.BindUFunction(this, "FireRateTimeElapsed", Instigator);
	GetWorld()->GetTimerManager().SetTimer(TimerHandleFireRate, DelegateFireRate, FireRateDelay, false);
	FTimerHandle TimerHandleSpawnDelay;
	FTimerDelegate DelegateSpawnDelay;
	DelegateSpawnDelay.BindUFunction(this, "SpawnDelayTimeElapsed", Instigator);
	GetWorld()->GetTimerManager().SetTimer(TimerHandleSpawnDelay, DelegateFireRate, SpawnDelay, false);
}

FTransform UGAction_Attack::CalculateProjectileTransform(ACharacter* InstigatorActor)
{
	FVector HandLocation = InstigatorActor->GetMesh()->GetSocketLocation("middle_01_lSocket");
	//UE_LOG(LogTemp, Log, TEXT("Hand location: %s"), *HandLocation.ToString());
	FRotator SpawnRotator;
	if(Cast<AGCharacter>(InstigatorActor))
	{
		SpawnRotator = InstigatorActor->GetMesh()->GetRelativeRotation();
		//SpawnRotator.Yaw += 90;
	}
	else if(Cast<AGAICharacter>(InstigatorActor))
	{
		SpawnRotator = InstigatorActor->GetActorForwardVector().Rotation();
	}
	SpawnRotator.Pitch = 0;
	const FTransform SpawnTM = FTransform(SpawnRotator, HandLocation);
	//DrawDebugLine(GetWorld(), HandLocation, SpawnRotator.)
	return SpawnTM;
}

void UGAction_Attack::FireRateTimeElapsed(ACharacter* Instigator)
{
	StopAction(Instigator);
}

void UGAction_Attack::SpawnDelayTimeElapsed(ACharacter* Instigator)
{
}
