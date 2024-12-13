// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/KasaneAnimInstance.h"
#include "Character/Character_Kasane.h"


void UKasaneAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	OwningKasane = Cast<ACharacter_Kasane>(OwningCharacter);
}

void UKasaneAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (OwningCharacter == nullptr || OwningMovementComponent == nullptr)
	{
		return;
	}

	JumpCount = OwningCharacter->JumpCurrentCount;
	VelocityZ = OwningCharacter->GetVelocity().Z;
	bHasAcceleration = OwningKasane->NeedToMove();
	bNeedToStop |= OwningKasane->GetMovementElapsedTime() > 1.f;
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
