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
#include "BaseFunctionLibrary.h"
#include "Components/ComboSystemComponent.h"
#include "Components/UnlockSystemComponent.h"
#include "Kismet/KismetMathLibrary.h"

ACharacter_Kasane::ACharacter_Kasane()
{
	USkeletalMeshComponent* MainBody = GetMesh();
	MainBody->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -100.f), FRotator(0.f, -90.f, 0.f));
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
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 100.f);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 5.f;

	UCameraComponent* MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	MainCamera->bUsePawnControlRotation = false;

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;
	Movement->MaxWalkSpeed = 800;
	Movement->RotationRate = FRotator(0.f, 600.f, 0.f);
	OriginRotationRate = Movement->RotationRate;
	Movement->MaxAcceleration = 4096;
	Movement->GravityScale = 3.f;
	Movement->bApplyGravityWhileJumping = false;


	OverrideInputComponentClass = UBaseInputComponent::StaticClass();
	BaseAbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	CreateDefaultSubobject<UUnlockSystemComponent>(TEXT("UnlockSystemComponent"));
	ComboSystemComponent = CreateDefaultSubobject<UComboSystemComponent>(TEXT("ComboSystemComponent"));

	MovementModeChangedDelegate.AddDynamic(this, &ACharacter_Kasane::OnFalling);


	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Game/Resources/Weapons/WP0200/WP200_Base.WP200_Base"));
	if (WeaponMesh.Succeeded())
	{
		for (int i = 1; i <=6; i++)
		{
			USkeletalMeshComponent* WeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(FName(FString::Printf(TEXT("Weapon0%d"), i)));
			WeaponMeshComp->SetSkeletalMesh(WeaponMesh.Object);
			WeaponMeshComp->SetupAttachment(MainBody, FName(FString::Printf(TEXT("Weapon0%d"), i)));
			WeaponMeshComp->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
		}
	}
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
	check(DirectionInputConfig);

	if(UEnhancedInputLocalPlayerSubsystem* Subsystem 
		= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetController<APlayerController>()->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputConfig->DefaultInputMappingContext, 0);
		Subsystem->AddMappingContext(DirectionInputConfig->DefaultInputMappingContext, 1);
	}

	UBaseInputComponent* InputComp = Cast<UBaseInputComponent>(PlayerInputComponent);
	check(InputComp);
	InputComp->BindNativeInputAction(InputConfig, BaseGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ACharacter_Kasane::OnInputMoveTriggered);
	InputComp->BindNativeInputAction(InputConfig, BaseGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ACharacter_Kasane::UpdateMovementElapsedTime);
	InputComp->BindNativeInputAction(InputConfig, BaseGameplayTags::InputTag_Move, ETriggerEvent::Completed, this, &ACharacter_Kasane::ResetMovementElapsedTime);
	InputComp->BindNativeInputAction(InputConfig, BaseGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ACharacter_Kasane::OnInputLookTriggered);
	InputComp->BindAbilityInputAction(InputConfig, this, &ACharacter_Kasane::OnAbilityInputTriggered);
	InputComp->BindDirectionInput(DirectionInputConfig, this, &ACharacter_Kasane::PushInput);
	InputComp->BindActionInstanceWithTag(InputConfig, this);
}

void ACharacter_Kasane::OnInputMoveTriggered(const FInputActionValue& Value)
{
	if (NeedToMove() == false) return;
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	if (MovementVector.X != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.X);
	}
	if (MovementVector.Y != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.Y);
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

void ACharacter_Kasane::UpdateMovementElapsedTime(const FInputActionInstance& Instance)
{
	MovementElapsedTime = Instance.GetElapsedTime();
	MovementTriggeredTime = Instance.GetTriggeredTime();
	//Debug::Print(FString::Printf(TEXT("ElapsedTime %f: / TriggeredTime %f"), MovementElapsedTime, MovementTriggeredTime));
}

void ACharacter_Kasane::ResetMovementElapsedTime(const FInputActionValue& Value)
{
	MovementElapsedTime = 0.f;
	MovementTriggeredTime = 0.f;
}

void ACharacter_Kasane::OnAttackInputTriggered(FGameplayTag InputTag, const FInputActionInstance& Instance)
{
	ComboSystemComponent->ProcessInputAction(InputTag, ETriggerEvent::Triggered, Instance);
}

void ACharacter_Kasane::OnAttackInputCompleted(FGameplayTag InputTag, const FInputActionInstance& Instance)
{
	ComboSystemComponent->ProcessInputAction(InputTag, ETriggerEvent::Completed, Instance);
}


void ACharacter_Kasane::OnFalling(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	GetCharacterMovement()->RotationRate = GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling ?
		FallingRotationRate : OriginRotationRate;
}

void ACharacter_Kasane::PushInput(EBaseDirectionType Direction)
{
	GetWorldTimerManager().ClearTimer(DodgeThresholdTimer);
	switch (Direction)
	{
		case EBaseDirectionType::Left:
		case EBaseDirectionType::Right:
		DirectionHistory |= 0b1100;
			break;
		case EBaseDirectionType::Front:
		case EBaseDirectionType::Back:
		DirectionHistory |= 0b0011;
			break;
		default:
		break;
	}
	DirectionHistory &= static_cast<uint8>(Direction); 
	GetWorldTimerManager().SetTimer(DodgeThresholdTimer, this, &ACharacter_Kasane::ClearInputHistory, DodgeAllowThreshold, false);

}

uint8 ACharacter_Kasane::GetDirectionByHistory()
{
	uint8 Result = DirectionHistory;
	ClearInputHistory();
	return Result;
}

void ACharacter_Kasane::ActivateDash(bool bIsDashing)
{
	GetCharacterMovement()->MaxWalkSpeed = bIsDashing ? 1200.f : 800.f;
}

void ACharacter_Kasane::ClearInputHistory()
{
	DirectionHistory = static_cast<uint8>(EBaseDirectionType::Max);
}
