// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Character_Kasane.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/BaseInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "BaseFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "Camera/CameraActor.h"
#include "Components/ComboSystemComponent.h"
#include "Components/PsychokinesisComponent.h"
#include "Components/SASManageComponent.h"
#include "Components/SphereComponent.h"
#include "Components/TargetTrackingSpringArmComponent.h"
#include "Components/UnlockSystemComponent.h"
#include "Components/Combat/KasaneCombatComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/InventoryComponent.h"

ACharacter_Kasane::ACharacter_Kasane()
{
	IsAffectedByAccelAbility = false;
	USkeletalMeshComponent* MainBody = GetMesh();
	MainBody->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -100.f), FRotator(0.f, -90.f, 0.f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MainBodyMesh(TEXT("/Game/Resources/Characters/CH0200/CH200_Base.CH200_Base"));
	if (MainBodyMesh.Succeeded())
	{
		MainBody->SetSkeletalMesh(MainBodyMesh.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> MainBodyAnim(TEXT("/Game/_BP/Character/Kasane/Animation/ABP_KasaneAnimInstance.ABP_KasaneAnimInstance_C"));
	if (MainBodyAnim.Succeeded())
	{
		MainBody->SetAnimInstanceClass(MainBodyAnim.Class);
	}
	

	USkeletalMeshComponent* OutlineBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Outline"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> OutlineBodyMesh(TEXT("/Game/Resources/Characters/CH0200/CH200_Outline.CH200_Outline"));
	if (OutlineBodyMesh.Succeeded())
	{
		OutlineBody->SetSkeletalMesh(OutlineBodyMesh.Object);
		OutlineBody->SetupAttachment(MainBody);
		OutlineBody->SetLeaderPoseComponent(MainBody);
	}

	MainCapsule = GetCapsuleComponent();
	const float CapsuleRadius = 42.f;
	const float CapsuleHalfHeight = 96.f;
	MainCapsule->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);

	HitboxCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Hitbox"));
	HitboxCapsule->InitCapsuleSize(CapsuleRadius, CapsuleHalfHeight);
	HitboxCapsule->SetupAttachment(MainBody, FName("Waist"));
	HitboxCapsule->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	CameraBoom = CreateDefaultSubobject<UTargetTrackingSpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(MainBody, FName("Waist"));
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 100.f);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 5.f;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraRotationLagSpeed = 15.f;
	//CameraBoom->bUseCameraLagSubstepping = true;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	MainCamera->bUsePawnControlRotation = false;

	ComboDirectCameraActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("ComboDirectCameraActor"));
	ComboDirectCameraActor->SetChildActorClass(ACameraActor::StaticClass());
	ComboDirectCameraActor->SetupAttachment(MainBody, FName("CameraPos"));

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
	GetMesh()->SetAllowAnimCurveEvaluation(true);

	PsychBoundary = CreateDefaultSubobject<USphereComponent>(TEXT("PsychBoundary"));
	PsychBoundary->SetupAttachment(RootComponent);
	PsychBoundary->InitSphereRadius(1500.f);
	PsychokinesisComponent = CreateDefaultSubobject<UPsychokinesisComponent>(TEXT("PsychokinesisComponent"));
	USkeletalMeshComponent* PsychObject = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PsychObject"));
	//PsychObject->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	PsychObject->SetupAttachment(GetMesh());
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PsychObjectAsset(TEXT("/Game/Resources/Psychokinesis/Common/AS_Psy_Common.AS_Psy_Common"));
	if (PsychObjectAsset.Succeeded())
	{
		PsychObject->SetSkeletalMesh(PsychObjectAsset.Object);
		PsychObject->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PsychObject->SetHiddenInGame(true);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> PsychObjectAnimAsset(TEXT("/Game/_BP/Character/Kasane/PsychAnimation/ABP_Psych.ABP_Psych_C"));
	if (PsychObjectAnimAsset.Succeeded())
	{
		PsychObject->SetAnimInstanceClass(PsychObjectAnimAsset.Class);
	}
	PsychokinesisComponent->InitComponents(PsychBoundary, PsychObject);

	JustDodgeBoundary = CreateDefaultSubobject<USphereComponent>(TEXT("JustDodgeBoundary"));
	JustDodgeBoundary->SetupAttachment(MainBody, FName("Waist"));
	JustDodgeBoundary->InitSphereRadius(500.f);

	SASManageComponent = CreateDefaultSubobject<USASManageComponent>(TEXT("SASManager"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	// Attribute
	BaseAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("KasaneAttributeSet"));

	// Cpmbat
	KasaneCombatComponent = CreateDefaultSubobject<UKasaneCombatComponent>(TEXT("KasaneCombatComponent"));
	

	
	// SAS - Clone
	LeftCloneComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftClone"));
	RightCloneComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightClone"));
	if (MainBodyMesh.Succeeded())
	{
		LeftCloneComponent->SetSkeletalMesh(MainBodyMesh.Object);
		LeftCloneComponent->SetupAttachment(MainBody);
		LeftCloneComponent->SetLeaderPoseComponent(MainBody);
		LeftCloneComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LeftCloneComponent->SetRelativeLocation(FVector(-100.f, 0.f, 0.f));
		
		RightCloneComponent->SetSkeletalMesh(MainBodyMesh.Object);
		RightCloneComponent->SetupAttachment(MainBody);
		RightCloneComponent->SetLeaderPoseComponent(MainBody);
		RightCloneComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		RightCloneComponent->SetRelativeLocation(FVector(100.f, 0.f, 0.f));
	}

	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponMesh(TEXT("/Game/Resources/Weapons/WP0200/WP200_Base.WP200_Base"));
	if (WeaponMesh.Succeeded())
	{
		const TArray TempBodies({MainBody, LeftCloneComponent, RightCloneComponent});
		for (auto TempBody : TempBodies)
		{
			for (int i = 1; i <=6; i++)
			{
				USkeletalMeshComponent* WeaponMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(FName(FString::Printf(TEXT("%s_Weapon0%d"), *TempBody->GetName(), i)));
				WeaponMeshComp->SetSkeletalMesh(WeaponMesh.Object);
				WeaponMeshComp->SetupAttachment(TempBody, FName(FString::Printf(TEXT("Weapon0%d"), i)));
				WeaponMeshComp->SetRelativeRotation(FRotator(0.f, 0.f, -90.f));
			}
		}
	}
	
}

void ACharacter_Kasane::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (StartupData.IsNull() == false)
	{
		if (UDataAsset_StartupBase* LoadedData = StartupData.LoadSynchronous())
		{
			LoadedData->GiveStartupAbilities(BaseAbilitySystemComponent);
		}
	}

	if (ComboSystemComponent)
	{
		ComboSystemComponent->InitReferences(this, JustDodgeBoundary);
		ComboSystemComponent->GrantAttackAbilites(BaseAbilitySystemComponent);
	}

	if (SASManageComponent)
	{
		SASManageComponent->InitReferences(this);
		SASManageComponent->GrantSASAbilites();
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
	InputComp->BindNativeInputAction(InputConfig, BaseGameplayTags::InputTag_Targeting_Toggle, ETriggerEvent::Triggered, this, &ACharacter_Kasane::OnTargetingInputTriggered);
	InputComp->BindNativeInputAction(InputConfig, BaseGameplayTags::InputTag_Item_Change, ETriggerEvent::Triggered, this, &ACharacter_Kasane::OnChangeItemInputTriggered);
	InputComp->BindAbilityInputAction(InputConfig, this, &ACharacter_Kasane::OnAbilityInputTriggered);
	InputComp->BindSASAbilityInputAction(InputConfig, this, &ACharacter_Kasane::OnSASAbilityInputTriggered);
	InputComp->BindDirectionInput(DirectionInputConfig, this, &ACharacter_Kasane::PushInput);
	InputComp->BindActionInstanceWithTag(InputConfig, this);
}

void ACharacter_Kasane::OnInputMoveTriggered(const FInputActionValue& Value)
{
	if (NeedToMove() == false) return;
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
	const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
	if (MovementVector.X != 0.f)
	{
		AddMovementInput(ForwardDirection, MovementVector.X);
	}
	if (MovementVector.Y != 0.f)
	{
		AddMovementInput(RightDirection, MovementVector.Y);
	}

	if (UBaseFunctionLibrary::NativeActorHasTag(this, BaseGameplayTags::Shared_Status_CanMove))
	{
		ComboSystemComponent->TryCancelAttackAbility();
		ComboSystemComponent->ResetWeaponCombo();
		if (GetCharacterMovement()->MovementMode != MOVE_Falling)
		{
			ComboSystemComponent->ResetBackstep();
		}
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
	CameraBoom->StartResetTimer();
}

void ACharacter_Kasane::OnTargetingInputTriggered(const FInputActionValue& Value)
{
	Debug::Print("Targeting Input");
	TArray<AActor*> TargetActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), TargetActors);
	TargetActors.Remove(this);
	CameraBoom->SetFoundTargets(TargetActors);
	CameraBoom->ToggleTargetTracking();
}


void ACharacter_Kasane::OnAbilityInputTriggered(FGameplayTag InputTag)
{
	if (UBaseFunctionLibrary::NativeActorHasTag(this, BaseGameplayTags::Shared_Status_CanAttack) == false) return;
	BaseAbilitySystemComponent->OnAbilityInputTriggered(InputTag);
}

void ACharacter_Kasane::OnSASAbilityInputTriggered(FGameplayTag InputTag)
{
	if (UBaseFunctionLibrary::NativeActorHasTag(this, BaseGameplayTags::Shared_Status_CanAttack) == false) return;
	SASManageComponent->OnSASInputTriggered(InputTag);
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
	
	if (PrevMovementMode == MOVE_Falling)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Character, BaseGameplayTags::Shared_Event_Grounded, FGameplayEventData());
	}
	GetCharacterMovement()->RotationRate = GetCharacterMovement()->MovementMode == MOVE_Falling ?
		FallingRotationRate : OriginRotationRate;
}

void ACharacter_Kasane::PushInput(EBaseDirectionType Direction)
{
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

FVector ACharacter_Kasane::GetInputDirection()
{
	FVector InputDirection(0.f);
	if (DirectionHistory & (static_cast<uint8>(EBaseDirectionType::Front) & 0b0011))
	{
		InputDirection += FVector::ForwardVector;
	}
	
	if (DirectionHistory & (static_cast<uint8>(EBaseDirectionType::Back) & 0b0011))
	{
		InputDirection += FVector::BackwardVector;
	}
	
	if (DirectionHistory & (static_cast<uint8>(EBaseDirectionType::Right) & 0b1100))
	{
		InputDirection += FVector::RightVector;
	}
	
	if (DirectionHistory & (static_cast<uint8>(EBaseDirectionType::Left) & 0b1100))
	{
		InputDirection += FVector::LeftVector;
	}

	return InputDirection;
}

void ACharacter_Kasane::ActivateDash(bool bIsDashing)
{
	GetCharacterMovement()->MaxWalkSpeed = bIsDashing ? 1200.f : 800.f;
}

UPawnCombatComponent* ACharacter_Kasane::GetPawnCombatComponent() const
{
	return  KasaneCombatComponent;	
}


void ACharacter_Kasane::ClearInputHistory()
{
	DirectionHistory = static_cast<uint8>(EBaseDirectionType::Max);
}

void ACharacter_Kasane::ChangeCamera(bool bUseMain)
{
	auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (bUseMain)
		PC->SetViewTargetWithBlend(this, 1.f);
	else
		PC->SetViewTargetWithBlend(ComboDirectCameraActor->GetChildActor(), 1.f);
}

void ACharacter_Kasane::ActivateAfterimage(bool InIsActive)
{
	if (AfterImageEffectSystem == nullptr) return;
	if (InIsActive)
	{
		AfterimageEffectComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
			AfterImageEffectSystem,
			GetMesh(),
			NAME_None,
			FVector(0.f,0.f,0.f),
			FRotator(0.f,0.f,0.f),
			EAttachLocation::Type::SnapToTarget,
			false);
	}
	else
	{
		if (AfterimageEffectComponent)
		{
			AfterimageEffectComponent->DestroyComponent();
		}
	}
}

void ACharacter_Kasane::ActivateCloneSkeletalMesh(bool InIsActive, int32 InCount)
{
	bool NeedToActivateLeftClone = true;
	bool NeedToActivateRightClone = true;
	if (InIsActive)
	{
		switch (InCount)
		{
			case 2:
				NeedToActivateLeftClone = false;
			case 1:
				NeedToActivateRightClone = false;
				break;
			default:
				break;
		}
	}
	LeftCloneComponent->SetHiddenInGame(NeedToActivateLeftClone, true);
	RightCloneComponent->SetHiddenInGame(NeedToActivateRightClone, true);
}

void ACharacter_Kasane::OnChangeItemInputTriggered(const FInputActionValue& Value)
{
	if (InventoryComponent == nullptr) return;
	float Axis = Value.Get<float>();
	if (Axis > 0.f)
	{
		InventoryComponent->ChangeIndex(false);
	}
	else
	{
		InventoryComponent->ChangeIndex(true);
	}
}

void ACharacter_Kasane::BeginPlay()
{
	Super::BeginPlay();
	ComboDirectCameraActor->CreateChildActor();
	ActivateCloneSkeletalMesh(false);
}
