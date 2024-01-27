// Fill out your copyright notice in the Description page of Project Settings.


#include "GTargetDummy.h"

#include "GAttributeComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AGTargetDummy::AGTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("BoxComp");
	RootComponent = BoxComp;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComp->SetupAttachment(BoxComp);

	AttributeComp = CreateDefaultSubobject<UGAttributeComponent>("AttributeComp");
	AttributeComp->MaxHealth = 100;
	AttributeComp->CurrentHealth = AttributeComp->MaxHealth;
}

// Called when the game starts or when spawned
void AGTargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGTargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

