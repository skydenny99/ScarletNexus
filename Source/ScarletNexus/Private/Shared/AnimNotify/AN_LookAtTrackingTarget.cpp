// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/AN_LookAtTrackingTarget.h"

#include "Character/Character_Kasane.h"
#include "Components/TargetTrackingSpringArmComponent.h"

AActor* UAN_LookAtTrackingTarget::GetTargetActor(AActor* Owner) const
{
	if (ACharacter_Kasane* Character = Cast<ACharacter_Kasane>(Owner))
	{
		return Character->GetTargetTrackingComponent()->GetCurrentTarget();
	}
	return nullptr;
}
