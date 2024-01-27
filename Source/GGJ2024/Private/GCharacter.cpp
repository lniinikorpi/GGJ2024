// Fill out your copyright notice in the Description page of Project Settings.


#include "GCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "EnhancedInputComponent.h"
#include "GAttributeComponent.h"
#include "Action/GActionComponent.h"

// Sets default values
AGCharacter::AGCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	ActionComp = CreateDefaultSubobject<UGActionComponent>("ActionComp");
	AttributeComp = CreateDefaultSubobject<UGAttributeComponent>("AttributeComp");
	AttributeComp->MaxHealth = 100;
	AttributeComp->CurrentHealth = AttributeComp->MaxHealth;

	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>("ProjectileSpawn");
	ProjectileSpawn->SetupAttachment(GetMesh());

	GetCharacterMovement()->bOrientRotationToMovement = false;
}

// Called when the game starts or when spawned
void AGCharacter::BeginPlay()
{
	Super::BeginPlay();

	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(!PlayerController)
	{
		return;
	}
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if(!SubSystem)
	{
		return;
	}
	SubSystem->AddMappingContext(MappingContext, 0);
}

void AGCharacter::Move(const FInputActionValue& Value)
{
	FRotator ControlRot = GetControlRotation();

	const FVector2D MovementVector = Value.Get<FVector2D>();

	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	AddMovementInput(ControlRot.Vector(), MovementVector.Y);
	const FVector Right = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(Right, MovementVector.X);
}

void AGCharacter::MouseLook(const FInputActionValue& Value)
{
	// Get mouse position
	APlayerController* pc = Cast<APlayerController>(GetController());

	float mouseX = 0.f;
	float mouseY = 0.f;

	FVector mousePos = FVector::ZeroVector;

	FHitResult Hitresult;
	if (pc->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), false, Hitresult))
	{
		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(Cast<APlayerController>(GetController()), Hitresult.ImpactPoint, MousePosition, true);
		//UE_LOG(LogTemp, Log, TEXT("%s"), *MousePosition.ToString());
		mousePos = FVector(mouseX, mouseY, 0.0f);
		const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());

		//FVector middleOfScreen = FVector(ViewportSize.X / 2, ViewportSize.Y / 2, 0.0f);
		FVector directionToMouse = Hitresult.ImpactPoint - GetActorLocation();
		directionToMouse.Z = 0;
		directionToMouse.Normalize();
		//UE_LOG(LogTemp, Log, TEXT("%s"), *ViewportSize.ToString());
		//UE_LOG(LogTemp, Log, TEXT("%s"), *Hitresult.ImpactPoint.ToString());
		FRotator CharacterRotation = directionToMouse.Rotation();
		//CharacterRotation.Yaw -= 90;
		GetMesh()->SetRelativeRotation(CharacterRotation);
	}
	//UE_LOG(LogTemp, Log, TEXT("%s"), *mousePos.ToString());
}

void AGCharacter::PrimaryAttack(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Log, TEXT("Poop throwed"));
	ActionComp->StartPrimaryAttackAction();
}

// Called every frame
void AGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AGCharacter::MouseLook);
		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Triggered, this, &AGCharacter::PrimaryAttack);
	}
}

