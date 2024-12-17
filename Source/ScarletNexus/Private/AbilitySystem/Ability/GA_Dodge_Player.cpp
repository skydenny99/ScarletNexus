// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_Dodge_Player.h"

#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"
#include "AnimInstance/KasaneAnimInstance.h"
#include "BaseType/BaseEnumType.h"
#include "Character/BaseCharacter.h"
#include "Character/Character_Kasane.h"
#include "Components/ComboSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


bool operator==(uint8 Lhs, EBaseDirectionType Type)
{
	return Lhs == static_cast<uint8>(Type);
}


void UGA_Dodge_Player::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	KasaneAnimInstance = Cast<UKasaneAnimInstance>(DodgeCharacter->GetMesh()->GetAnimInstance());
	check(KasaneAnimInstance);
	KasaneAnimInstance->OnDodgeEnd.BindUObject(this, &UGA_Dodge_Player::OnEndDodge);
	DodgeCharacter->MovementModeChangedDelegate.AddDynamic(this, &UGA_Dodge_Player::ResetDodgeCount);
	DodgeMovementComponent = DodgeCharacter->GetCharacterMovement();
	check(DodgeMovementComponent);
}

bool UGA_Dodge_Player::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return DodgeMovementComponent->IsFalling() == false || DodgeCount < MaxDodgeCount;
	}
	return false;
}

void UGA_Dodge_Player::GetCharacterDodgeDirection(EBaseDirectionType& DirectionResult)
{
	ACharacter_Kasane* Kasane = Cast<ACharacter_Kasane>(DodgeCharacter);
	check(Kasane);
	uint8 DirectionInput = Kasane->GetDirectionByHistory();
	if (DirectionInput == EBaseDirectionType::Max)
	{
		DirectionResult = EBaseDirectionType::Front;
		return;
	}
	
	
	FVector InputDirection(0.f);
	if (DirectionInput & (static_cast<uint8>(EBaseDirectionType::Front) & 0b0011))
	{
		InputDirection += FVector::ForwardVector;
	}
	
	if (DirectionInput & (static_cast<uint8>(EBaseDirectionType::Back) & 0b0011))
	{
		InputDirection += FVector::BackwardVector;
	}
	
	if (DirectionInput & (static_cast<uint8>(EBaseDirectionType::Right) & 0b1100))
	{
		InputDirection += FVector::RightVector;
	}
	
	if (DirectionInput & (static_cast<uint8>(EBaseDirectionType::Left) & 0b1100))
	{
		InputDirection += FVector::LeftVector;
	}
	
	FVector LookDirection = FRotator(0.f, DodgeCharacter->GetControlRotation().Yaw, 0.f).RotateVector(InputDirection);
	FVector CharacterForward = DodgeCharacter->GetActorForwardVector();
	FVector CharacterRight = DodgeCharacter->GetActorRightVector();

	LookDirection.Normalize();
	float VerticalDot = FVector::DotProduct(LookDirection, CharacterForward);
	float HorizontalDot = FVector::DotProduct(LookDirection, CharacterRight);

	// Check Nearest Vector
	if (FMath::Abs(VerticalDot) >= FMath::Abs(HorizontalDot))
	{
		if (VerticalDot > 0.f) // Forward
		{
			DirectionResult = EBaseDirectionType::Front;
			Debug::Print("Forward");
		}
		else // Backward
		{
			DirectionResult = EBaseDirectionType::Back;
			Debug::Print("Back");
			LookDirection = UKismetMathLibrary::RotateAngleAxis(LookDirection, 180, FVector::UpVector);
		}
	}
	else
	{
		if (HorizontalDot > 0.f) // Right
		{
			DirectionResult = EBaseDirectionType::Right;
			Debug::Print("Right");	
			LookDirection = UKismetMathLibrary::RotateAngleAxis(LookDirection, -90, FVector::UpVector);
		}
		else // Left
		{
			DirectionResult = EBaseDirectionType::Left;
			Debug::Print("Left");
			LookDirection = UKismetMathLibrary::RotateAngleAxis(LookDirection, 90, FVector::UpVector);
		}
	}

	FRotator TargetRot = UKismetMathLibrary::FindLookAtRotation(FVector(0.f), LookDirection);
	DodgeCharacter->SetActorRotation(TargetRot);
}

void UGA_Dodge_Player::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	EBaseDirectionType DodgeDir = EBaseDirectionType::Max;
	GetCharacterDodgeDirection(DodgeDir);
	PlayDodgeAnimation(DodgeDir);
	UBaseFunctionLibrary::AddPlaygameTagToActor(DodgeCharacter, BaseGameplayTags::Shared_Status_CanMove);
	UBaseFunctionLibrary::AddPlaygameTagToActor(DodgeCharacter, BaseGameplayTags::Player_Status_Move_Dodge);
	if (DodgeMovementComponent->IsFalling())
		DodgeCount++;
}

void UGA_Dodge_Player::PlayDodgeAnimation(EBaseDirectionType Direction)
{
	DodgeMovementComponent->Velocity = FVector::ZeroVector;
	DodgeMovementComponent->GravityScale = 0;
	KasaneAnimInstance->Dodge(Direction);
	
	ACharacter_Kasane* Kasane = Cast<ACharacter_Kasane>(DodgeCharacter);
	Kasane->ActivateDash(true);
	Kasane->GetComboSystemComponent()->ResetWeaponCombo();
}

void UGA_Dodge_Player::OnEndDodge()
{
	FVector Velocity = DodgeMovementComponent->Velocity;
	Velocity /= 3.f;
	Velocity.Z = 0;
	DodgeMovementComponent->Velocity = Velocity;
	DodgeMovementComponent->GravityScale = 3;
	UBaseFunctionLibrary::RemovePlayGameTagFromActor(DodgeCharacter, BaseGameplayTags::Player_Status_Move_Dodge);
	K2_EndAbility();
}

void UGA_Dodge_Player::ResetDodgeCount(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	if (DodgeMovementComponent)
	{
		if (DodgeMovementComponent->MovementMode != MOVE_Falling)
		{
			DodgeCount = 0;
		}
	}
}
