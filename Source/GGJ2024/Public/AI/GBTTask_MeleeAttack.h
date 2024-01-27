// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GBTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class GGJ2024_API UGBTTask_MeleeAttack : public UBTTaskNode
{
	GENERATED_BODY()


	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UGBTTask_MeleeAttack();
};
