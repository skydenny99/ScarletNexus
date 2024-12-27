// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/KasaneAnimInstance.h"
#include "Character/Character_Kasane.h"
#include "Components/ComboSystemComponent.h"
#include "Components/PsychokinesisComponent.h"


void UKasaneAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwningKasane = Cast<ACharacter_Kasane>(OwningCharacter);
}

void UKasaneAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (OwningKasane == nullptr || OwningCharacter == nullptr || OwningMovementComponent == nullptr)
	{
		return;
	}

	JumpCount = OwningCharacter->JumpCurrentCount;
	VelocityZ = OwningCharacter->GetVelocity().Z;
	bHasAcceleration = OwningKasane->NeedToMove();
	bNeedToStop |= OwningKasane->GetMovementElapsedTime() > 1.f;
	AttackTag = OwningKasane->GetComboSystemComponent()->GetAttackType();
}

void UKasaneAnimInstance::Dodge(EBaseDirectionType Direction)
{
	bDoingDodge = true;
	DodgeDirection = Direction;
}

void UKasaneAnimInstance::DodgeEnd()
{
	OnDodgeEnd.ExecuteIfBound();
}

USkeletalMeshComponent* UKasaneAnimInstance::GetPsychSkeletalMesh() const
{
	if (OwningKasane)
	{
		return OwningKasane->GetPsychokinesisComponent()->GetPsychSkeletalMesh();
	}
	return nullptr;
}
