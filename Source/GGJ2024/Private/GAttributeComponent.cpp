// Fill out your copyright notice in the Description page of Project Settings.


#include "GAttributeComponent.h"

#include "GGameModeBase.h"


UGAttributeComponent::UGAttributeComponent()
{
}

// Called when the game starts
void UGAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

}
UGAttributeComponent* UGAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (!FromActor)
	{
		return nullptr;
	}

	return FromActor->FindComponentByClass<UGAttributeComponent>();
}

bool UGAttributeComponent::IsActorAlive(AActor* FromActor)
{
	if (!FromActor)
	{
		return false;
	}

	UGAttributeComponent* AttributeComponent = GetAttributes(FromActor);
	if (!AttributeComponent)
	{
		return false;
	}

	return AttributeComponent->IsAlive();
}

bool UGAttributeComponent::IsAlive()
{
	return CurrentHealth > 0.0f;
}

bool UGAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float HealthDelta)
{
	if (!GetOwner()->CanBeDamaged() && HealthDelta < 0.0f)
	{
		return false;
	}

	if (HealthDelta < 0.0f)
	{
		//HealthDelta *= CVarDamageMultiplier.GetValueOnGameThread();
	}

	float OldHealth = CurrentHealth;
	CurrentHealth += HealthDelta;

	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);

	const bool bDidHealthChange = OldHealth != CurrentHealth;

	if (bDidHealthChange)
	{
		OnHealthChanged.Broadcast(InstigatorActor, this, CurrentHealth, HealthDelta);
		UE_LOG(LogTemp, Log, TEXT("%s current health is: %f"), *GetOwner()->GetActorNameOrLabel(), CurrentHealth)
		//Pawn died
		if (HealthDelta < 0 && CurrentHealth <= 0)
		{
			GetWorld()->DestroyActor(GetOwner());
			AGGameModeBase* GM = GetWorld()->GetAuthGameMode<AGGameModeBase>();
			if (GM)
			{
				GM->OnActorKilled(GetOwner(), InstigatorActor);
			}
		}
	}

	return bDidHealthChange;
}

float UGAttributeComponent::HealthNormalized()
{
	return CurrentHealth / MaxHealth;
}

