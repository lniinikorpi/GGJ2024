// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GAIController.generated.h"

class UGAttributeComponent;
/**
 * 
 */
UCLASS()
class GGJ2024_API AGAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UGAttributeComponent* OwningComp, float NewHealth, float Delta);

	void PostInitializeComponents() override;

	void OnPossess(APawn* InPawn) override;
};
