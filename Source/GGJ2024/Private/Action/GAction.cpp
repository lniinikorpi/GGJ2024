// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/GAction.h"
#include "Action/GActionComponent.h"


UGAction::UGAction()
{
}

UGActionComponent* UGAction::GetOwningComponent() const
{
	return Cast<UGActionComponent>(GetOuter());
}

UWorld* UGAction::GetWorld() const
{
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());
	if (!Comp)
	{
		return nullptr;
	}
	return Comp->GetWorld();
}

bool UGAction::CanStart_Implementation(AActor* InstigatorActor)
{
	if (IsRunning())
	{
		return false;
	}
	UGActionComponent* Comp = GetOwningComponent();
	return !Comp->ActiveGameplayTags.HasAny(BlockedTags);
}

void UGAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running %s"), *GetNameSafe(this));

	UGActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.AppendTags(GrantsTags);
	bIsRunning = true;
}

void UGAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running stopped %s"), *GetNameSafe(this));

	UGActionComponent* Comp = GetOwningComponent();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTags);
	bIsRunning = false;
}

bool UGAction::IsRunning()
{
	return bIsRunning;
}
