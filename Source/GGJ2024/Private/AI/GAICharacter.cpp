// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/GAICharacter.h"

#include "GAttributeComponent.h"
#include "Action/GActionComponent.h"

// Sets default values
AGAICharacter::AGAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AttributeComp = CreateDefaultSubobject<UGAttributeComponent>("AttributeComponent");
	AttributeComp->MaxHealth = 50;
	AttributeComp->CurrentHealth = AttributeComp->MaxHealth;
	ActionComponent = CreateDefaultSubobject<UGActionComponent>("ActionComponent");
	
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AGAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

