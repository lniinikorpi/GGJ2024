// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "GAction.generated.h"

class UGActionComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class GGJ2024_API UGAction : public UObject
{
	GENERATED_BODY()
protected:

	UFUNCTION(BlueprintCallable, Category = "Action")
	UGActionComponent* GetOwningComponent() const;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;

	bool bIsRunning;

public:
	UGAction();

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	bool bIsAutoStart;

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning();

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	bool CanStart(AActor* InstigatorActor);

	UFUNCTION(BlueprintNativeEvent, Category = "Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Action")
	void StopAction(AActor* Instigator);

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	FName ActionName;

	UWorld* GetWorld() const override;
	
};
