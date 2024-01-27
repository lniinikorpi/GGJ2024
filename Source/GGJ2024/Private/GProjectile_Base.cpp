// Fill out your copyright notice in the Description page of Project Settings.


#include "GProjectile_Base.h"

#include "GGlobalFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AGProjectile_Base::AGProjectile_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComponent->SetupAttachment(SphereComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	ProjectileMovementComp->InitialSpeed = 1000;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;

	DamageAmount = 40;
}

// Called when the game starts or when spawned
void AGProjectile_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGProjectile_Base::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AGProjectile_Base::OnOverLapBegin);
}

void AGProjectile_Base::OnOverLapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapping: %s"), *OtherActor->GetActorNameOrLabel());
	if(OtherActor == GetInstigator())
	{
		return;
	}
	UGGlobalFunctionLibrary::ApplyDamage(GetInstigator(), OtherActor, DamageAmount);
	GetWorld()->DestroyActor(this);
}

// Called every frame
void AGProjectile_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

