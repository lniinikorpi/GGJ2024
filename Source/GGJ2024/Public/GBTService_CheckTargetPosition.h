// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "GBTService_CheckTargetPosition.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2024_API UGBTService_CheckTargetPosition : public UBTService
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, Category = "AI");
	FBlackboardKeySelector IsInMeleeRangeKey;

	UPROPERTY(EditAnywhere, Category="AI")
	float MinDistance;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
