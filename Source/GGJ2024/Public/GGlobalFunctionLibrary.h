// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GGlobalFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2024_API UGGlobalFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static bool ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& HitResult);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static void ChangeCredits(AActor* OwningActor, int32 Delta);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	static int32 GetPlayerCredits(AActor* OwningActor);
};
