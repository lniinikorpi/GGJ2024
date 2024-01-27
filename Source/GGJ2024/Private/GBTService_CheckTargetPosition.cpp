// Fill out your copyright notice in the Description page of Project Settings.


#include "GBTService_CheckTargetPosition.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include <AIController.h>

void UGBTService_CheckTargetPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return;
	}
	AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetActor"));
	if (!TargetActor)
	{
		return;
	}
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return;
	}
	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn)
	{
		return;
	}
	FVector TargetLocation = TargetActor->GetActorLocation();
	float Distance = FVector::Distance(TargetLocation, AIPawn->GetActorLocation());
	bool bIsInRange = Distance < MinDistance;
	BlackboardComponent->SetValueAsBool(IsInMeleeRangeKey.SelectedKeyName, bIsInRange);
}
