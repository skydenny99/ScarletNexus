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
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 150.f);
	CameraBoom->TargetArmLength = 800.f;

	UCameraComponent* MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	MainCamera->bUsePawnControlRotation = false;

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;
	Movement->MaxWalkSpeed = 800;
	Movement->RotationRate = FRotator(0.f, 1000.f, 0.f);
	OriginRotationRate = Movement->RotationRate;
	Movement->MaxAcceleration = 4096;


	OverrideInputComponentClass = UBaseInputComponent::StaticClass();
	BaseAbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	MovementModeChangedDelegate.AddDynamic(this, &ACharacter_Kasane::OnFalling);
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
	InputComp->BindNativeInputAction(InputConfig, BaseGameplayTags::InputTag_Move, ETriggerEvent::Started, this, &ACharacter_Kasane::OnInputMoveStarted);
	InputComp->BindNativeInputAction(InputConfig, BaseGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ACharacter_Kasane::OnInputMoveTriggered);
	InputComp->BindNativeInputAction(InputConfig, BaseGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ACharacter_Kasane::OnInputLookTriggered);
	InputComp->BindAbilityInputAction(InputConfig, this, &ACharacter_Kasane::OnAbilityInputTriggered);
}

void ACharacter_Kasane::OnInputMoveStarted(const FInputActionValue& Value)
{
	GetWorldTimerManager().ClearTimer(DodgeThresholdTimer);
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (MovementVector.X > 0.f)
	{
		UBaseFunctionLibrary::AddPlaygameTagToActor(this, BaseGameplayTags::InputTag_History_Move_Vertical_Forward);
	}
	else if (MovementVector.X < 0.f)
	{
		UBaseFunctionLibrary::AddPlaygameTagToActor(this, BaseGameplayTags::InputTag_History_Move_Vertical_Backward);
	}

	if (MovementVector.Y > 0.f)
	{
		UBaseFunctionLibrary::AddPlaygameTagToActor(this, BaseGameplayTags::InputTag_History_Move_Horizontal_Right);
	}
	else if (MovementVector.Y < 0.f)
	{
		UBaseFunctionLibrary::AddPlaygameTagToActor(this, BaseGameplayTags::InputTag_History_Move_Horizontal_Left);
	}
	GetWorldTimerManager().SetTimer(DodgeThresholdTimer, this, &ACharacter_Kasane::ResetDodgeDirectionHistory, DodgeAllowThreshold, false);

	//if(FMath::IsNearlyZero(GetVelocity().Length()))
	//	RotateCharacterToNearestStandardDirection();
}

void ACharacter_Kasane::OnInputMoveTriggered(const FInputActionValue& Value)
{
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

void ACharacter_Kasane::ResetDodgeDirectionHistory()
{
	UBaseFunctionLibrary::RemovePlayGameTagFromActor(this, BaseGameplayTags::InputTag_History_Move_Horizontal_Left);
	UBaseFunctionLibrary::RemovePlayGameTagFromActor(this, BaseGameplayTags::InputTag_History_Move_Horizontal_Right);
	UBaseFunctionLibrary::RemovePlayGameTagFromActor(this, BaseGameplayTags::InputTag_History_Move_Vertical_Forward);
	UBaseFunctionLibrary::RemovePlayGameTagFromActor(this, BaseGameplayTags::InputTag_History_Move_Vertical_Backward);
}

void ACharacter_Kasane::OnFalling(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	GetCharacterMovement()->RotationRate = GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling ?
		FallingRotationRate : OriginRotationRate;
}

void ACharacter_Kasane::RotateCharacterToNearestStandardDirection()
{
	const FRotator DesiredForwardRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	FVector DesiredForwardVector = DesiredForwardRotation.Vector();
	float HorizontalDotProduct = DesiredForwardVector.Dot(GetActorRightVector().GetSafeNormal());
	float VerticalDotProduct = DesiredForwardVector.Dot(GetActorForwardVector().GetSafeNormal());

	FVector ActorDirectionVector;
	// 가장 가까운 기준 벡터를 골라 전환
	if (FMath::Abs(VerticalDotProduct) >= FMath::Abs(HorizontalDotProduct))
	{
		if (VerticalDotProduct > 0) // 정면
		{
			ActorDirectionVector =  GetActorForwardVector();
			Debug::Print("Rotate Character To Front");
		}
		else // 후면
		{
			ActorDirectionVector = GetActorForwardVector();
			Debug::Print("Rotate Character To Back");
		}
	}
	else
	{
		if (HorizontalDotProduct > 0) // 오른쪽
		{
			ActorDirectionVector = GetActorRightVector();
			Debug::Print("Rotate Character To Right");
		}
		else // 왼쪽
		{
			ActorDirectionVector = GetActorRightVector();
			Debug::Print("Rotate Character To Left");
		}
	}
	SetActorRotation((DesiredForwardVector - ActorDirectionVector.GetSafeNormal2D()).Rotation());
}

void ACharacter_Kasane::BP_GetCurrentChracterDirection(EBaseDirectionType& OutDirectionType)
{
	GetCurrentChracterDirection(OutDirectionType);
}

void ACharacter_Kasane::GetCurrentChracterDirection(EBaseDirectionType& OutDirectionType)
{
	const FRotator DesiredForwardRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	FVector DesiredForwardVector = DesiredForwardRotation.RotateVector(GetActorForwardVector());

	float HorizontalDotProduct = DesiredForwardVector.Dot(GetActorRightVector());
	float VerticalDotProduct = DesiredForwardVector.Dot(GetActorForwardVector());

	// 가장 가까운 기준 벡터를 골라 전환
	OutDirectionType = EBaseDirectionType::InValid;

	if (FMath::IsNearlyEqual(VerticalDotProduct, 1)) // 정면
	{
		OutDirectionType = EBaseDirectionType::Front;
	}
	else if (FMath::IsNearlyEqual(VerticalDotProduct, -1))
	{
		OutDirectionType = EBaseDirectionType::Back;
	}


	if (FMath::IsNearlyEqual(HorizontalDotProduct, 1)) // 정면
	{
		OutDirectionType = EBaseDirectionType::Right;
	}
	else if (FMath::IsNearlyEqual(HorizontalDotProduct, -1))
	{
		OutDirectionType = EBaseDirectionType::Left;
	}
}
