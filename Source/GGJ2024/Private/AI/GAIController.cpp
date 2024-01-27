// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AGAIController::BeginPlay()
{
	Super::BeginPlay();
	if (ensureMsgf(BehaviorTree, TEXT("Behaviour tree is nullptr Please assign BehaviourTree in your AiController")))
	{
		RunBehaviorTree(BehaviorTree);
	}
	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!MyPawn)
	{
		return;
	}


	GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
}

void AGAIController::Tick(float DeltaSeconds)
{
	UObject* TargetObject = GetBlackboardComponent()->GetValueAsObject("TargetActor");
	if(!TargetObject)
	{
		return;
	}
	AActor* TargetActor = Cast<AActor>(TargetObject);
	if(!TargetActor)
	{
		return;
	}
	FVector Dir = TargetActor->GetActorLocation() - GetPawn()->GetActorLocation();
	Dir.Normalize();
	SetControlRotation(Dir.Rotation());
	//GEngine->AddOnScreenDebugMessage(0, 0, FColor::White, GetControlRotation().ToString());
}
