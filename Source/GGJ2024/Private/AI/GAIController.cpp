// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GAIController.h"

#include "GAttributeComponent.h"
#include "GGameModeBase.h"
#include "Action/GActionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"
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
	/*if(!GetBlackboardComponent()->GetValueAsBool("IsAlerted"))
	{
		return;
	}*/
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

void AGAIController::OnHealthChanged(AActor* InstigatorActor, UGAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	GetBlackboardComponent()->SetValueAsBool("IsAlerted", true);
	UGActionComponent* ActionComp = InstigatorActor->GetComponentByClass<UGActionComponent>();
	if(ActionComp)
	{
		if (ActionComp->ActiveGameplayTags.HasTag(Cast<AGGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->HumanTag))
		{
			return;
		}
	}

	UCharacterMovementComponent* MoveComp = Cast<UCharacterMovementComponent>(Cast<APawn>(InstigatorActor)->GetMovementComponent());
	if (MoveComp)
	{
		MoveComp->bOrientRotationToMovement = false;
	}
}

void AGAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AGAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UGAttributeComponent::GetAttributes(InPawn)->OnHealthChanged.AddDynamic(this, &AGAIController::OnHealthChanged);
	UCharacterMovementComponent* MoveComp = Cast<UCharacterMovementComponent>(InPawn->GetMovementComponent());
	if (MoveComp)
	{
		UGActionComponent* ActionComp = InPawn->GetComponentByClass<UGActionComponent>();
		if (ActionComp)
		{
			if (ActionComp->ActiveGameplayTags.HasTag(Cast<AGGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->HumanTag))
			{
				MoveComp->bOrientRotationToMovement = true;
			}
			else
			{
				MoveComp->bOrientRotationToMovement = false;
			}
		}
	}
}
