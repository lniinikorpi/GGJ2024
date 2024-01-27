// Fill out your copyright notice in the Description page of Project Settings.


#include "GGlobalFunctionLibrary.h"

#include "GAttributeComponent.h"

bool UGGlobalFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	UGAttributeComponent* AttributeComponent = UGAttributeComponent::GetAttributes(TargetActor);
	if (!AttributeComponent)
	{
		return false;
	}
	return AttributeComponent->ApplyHealthChange(DamageCauser, -DamageAmount);
}

bool UGGlobalFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount,
	const FHitResult& HitResult)
{
	return false;
}

void UGGlobalFunctionLibrary::ChangeCredits(AActor* OwningActor, int32 Delta)
{
}

int32 UGGlobalFunctionLibrary::GetPlayerCredits(AActor* OwningActor)
{
	//TODO something
	return 0;
}
