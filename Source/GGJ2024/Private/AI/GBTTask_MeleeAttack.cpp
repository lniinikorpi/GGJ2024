// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GBTTask_MeleeAttack.h"

#include "AIController.h"
#include "Action/GActionComponent.h"
#include "AI/GAICharacter.h"

UGBTTask_MeleeAttack::UGBTTask_MeleeAttack()
{
}

EBTNodeResult::Type UGBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (!MyController)
	{
		return EBTNodeResult::Failed;
	}
	//UE_LOG(LogTemp, Warning, TEXT("%s is attacking"), *MyController->GetPawn()->GetActorNameOrLabel());
	Cast<AGAICharacter>(MyController->GetPawn())->GetComponentByClass<UGActionComponent>()->StartPrimaryAttackAction();
	return EBTNodeResult::Succeeded;
}

