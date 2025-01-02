// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/ANS_CameraLookAtOverrideTarget.h"

#include "Character/Character_Kasane.h"
#include "Components/TargetTrackingSpringArmComponent.h"

FVector UANS_CameraLookAtOverrideTarget::GetLookAtTargetLocation(AActor* Owner) const
{
	if (Owner == nullptr)
		return FVector::ZeroVector;
	if (ACharacter_Kasane* Character = Cast<ACharacter_Kasane>(Owner))
	{
		AActor* Target = Character->GetTargetTrackingComponent()->GetOverrideTarget();
		return Target ? Target->GetActorLocation() : FVector::ZeroVector;
	}
	return FVector::ZeroVector;
}
