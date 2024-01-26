// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "GActionComponent.generated.h"


class UGAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ2024_API UGActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGActionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool AddAction(AActor* InstigatorActor, TSubclassOf<UGAction> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void RemoveAction(UGAction* ActionToRemove);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);

	bool HasAction(FName ActionName);

	UFUNCTION(BlueprintCallable, Category="Actions")
	void StartPrimaryAttackAction();

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void StartSecondaryAttackAction();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Actions")
	TSubclassOf<UGAction> PrimaryAttackActionClass;

	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	TSubclassOf<UGAction> SecondaryAttackActionClass;

	UPROPERTY(EditDefaultsOnly, Category = "Actions")
	TArray<UGAction*> Actions;

	UPROPERTY(EditAnywhere, Category = "Actions")
	TArray<TSubclassOf<UGAction>> DefaultActions;
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
