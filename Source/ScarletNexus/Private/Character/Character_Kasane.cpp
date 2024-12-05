// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Character_Kasane.h"
#include "Components/BaseInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "BaseDebugHelper.h"

ACharacter_Kasane::ACharacter_Kasane()
{
	USkeletalMeshComponent* MainBody = GetMesh();
	MainBody->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainBodyMesh(TEXT("/Game/Resources/Characters/CH0200/CH200_Base.CH200_Base"));
	if (MainBodyMesh.Succeeded())
	{
		MainBody->SetSkeletalMesh(MainBodyMesh.Object);
	}

	USkeletalMeshComponent* OutlineBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Outline"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> OutlineBodyMesh(TEXT("/Game/Resources/Characters/CH0200/CH200_Outline.CH200_Outline"));
	if (OutlineBodyMesh.Succeeded())
	{
		OutlineBody->SetSkeletalMesh(OutlineBodyMesh.Object);
		OutlineBody->SetupAttachment(MainBody);
		OutlineBody->SetLeaderPoseComponent(MainBody);
	}

	UCapsuleComponent* MainCapsule = GetCapsuleComponent();
	const float CapsuleRadius = 42.f;
	const float CapsuleHalfHeight = 96.f;
	MainCapsule->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);

	UCapsuleComponent* HitboxCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hitbox"));
	HitboxCapsule->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);
	HitboxCapsule->SetupAttachment(MainBody, FName("Waist"));
	HitboxCapsule->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	USpringArmComponent* CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(MainBody, FName("Waist"));
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->TargetArmLength = 200.f;

	UCameraComponent* MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	MainCamera->bUsePawnControlRotation = false;

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;


	OverrideInputComponentClass = UBaseInputComponent::StaticClass();
	BaseAbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void ACharacter_Kasane::PossessedBy(AController* NewController)
{
	if (StartupData.IsNull() == false)
	{
		if (UDataAsset_StartupBase* LoadedData = StartupData.LoadSynchronous())
		{
			LoadedData->GiveStartupAbilities(BaseAbilitySystemComponent);
		}
	}
}

void ACharacter_Kasane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	check(InputConfig);

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem 
		= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetController<APlayerController>()->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputConfig->DefaultInputMappingContext, 0);
	}

	UBaseInputComponent* InputComp = Cast<UBaseInputComponent>(PlayerInputComponent);
	check(InputComp);
	InputComp->BindNativeInputAction(InputConfig, BaseGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ACharacter_Kasane::OnInputMoveTriggered);
	InputComp->BindNativeInputAction(InputConfig, BaseGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ACharacter_Kasane::OnInputLookTriggered);
	InputComp->BindAbilityInputAction(InputConfig, this, &ACharacter_Kasane::OnAbilityInputTriggered);
}

void ACharacter_Kasane::OnInputMoveTriggered(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACharacter_Kasane::OnInputLookTriggered(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACharacter_Kasane::OnAbilityInputTriggered(FGameplayTag InputTag)
{
	BaseAbilitySystemComponent->OnAbilityInputTriggered(InputTag);
}
