// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/GAction_Attack.h"

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
}

void UGAction_Attack::ActionAttackTimeElapsed(ACharacter* Instigator)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Instigator;
	GetWorld()->SpawnActor<AActor>(ProjectileClass, CalculateProjectileTransform(Instigator), SpawnParams);

	StopAction(Instigator);
}

FTransform UGAction_Attack::CalculateProjectileTransform(ACharacter* InstigatorActor)
{
	FVector HandLocation = InstigatorActor->GetMesh()->GetSocketLocation("middle_01_lSocket");
	UE_LOG(LogTemp, Log, TEXT("Hand location: %s"), *HandLocation.ToString());
	if(HandLocation == FVector::Zero())
	{
		
	}
	FRotator SpawnRotator = InstigatorActor->GetMesh()->GetRelativeRotation();
	SpawnRotator.Pitch = 0;
	SpawnRotator.Yaw += 90;
	const FTransform SpawnTM = FTransform(SpawnRotator, HandLocation);
	return SpawnTM;
}
