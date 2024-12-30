// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/AN_LookAtPsychTarget.h"

#include "Actor/PsychokineticPropBase.h"
#include "Character/Character_Kasane.h"
#include "Components/PsychokinesisComponent.h"

AActor* UAN_LookAtPsychTarget::GetTargetActor(AActor* Owner) const
{
	if (ACharacter_Kasane* Character = Cast<ACharacter_Kasane>(Owner))
	{
		return Character->GetPsychokinesisComponent()->GetCurrentPsychTarget();
	}
	return nullptr;
}
