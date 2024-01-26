// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/GActionComponent.h"
#include "Action/GAction.h"

// Sets default values for this component's properties
UGActionComponent::UGActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGActionComponent::BeginPlay()
{
	Super::BeginPlay();
	for (TSubclassOf<UGAction> ActionClass : DefaultActions)
	{
		AddAction(GetOwner(), ActionClass);
	}
	AddAction(GetOwner(), PrimaryAttackActionClass);
}

bool UGActionComponent::AddAction(AActor* InstigatorActor, TSubclassOf<UGAction> ActionClass)
{
	if (!ActionClass)
	{
		return false;
	}

	UGAction* NewAction = NewObject<UGAction>(this, ActionClass);
	if (!NewAction)
	{
		return false;
	}

	if (HasAction(NewAction->ActionName))
	{
		return false;
	}

	Actions.Add(NewAction);
	if (NewAction->bIsAutoStart && NewAction->CanStart(InstigatorActor))
	{
		NewAction->StartAction(InstigatorActor);
	}
	return true;
}

void UGActionComponent::RemoveAction(UGAction* ActionToRemove)
{
	if (!ActionToRemove || ActionToRemove->IsRunning())
	{
		return;
	}
	Actions.Remove(ActionToRemove);
}

bool UGActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for (UGAction* Action : Actions)
	{
		if (!Action)
		{
			continue;
		}

		if (Action->ActionName != ActionName)
		{
			continue;
		}

		if (!Action->CanStart(Instigator))
		{
			FString FailedMsg = FString::Printf(TEXT("Failed to run %s"), *ActionName.ToString());
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FailedMsg);
			continue;
		}
		Action->StartAction(Instigator);
		return true;
	}
	return false;
}

bool UGActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UGAction* Action : Actions)
	{
		if (!Action)
		{
			continue;
		}

		if (Action->ActionName != ActionName)
		{
			continue;
		}

		if (!Action->IsRunning())
		{
			continue;
		}

		Action->StopAction(Instigator);
		return true;
	}
	return false;
}

bool UGActionComponent::HasAction(FName ActionName)
{
	for (UGAction* Action : Actions) {
		if (!Action->ActionName.IsEqual(ActionName))
		{
			continue;
		}
		return true;
	}
	return false;
}

void UGActionComponent::StartPrimaryAttackAction()
{
	UGAction* NewAction = NewObject<UGAction>(this, PrimaryAttackActionClass);
	StartActionByName(GetOwner(), NewAction->ActionName);
}

void UGActionComponent::StartSecondaryAttackAction()
{
	UGAction* NewAction = NewObject<UGAction>(this, SecondaryAttackActionClass);
	StartActionByName(GetOwner(), NewAction->ActionName);
}

// Called every frame
void UGActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

