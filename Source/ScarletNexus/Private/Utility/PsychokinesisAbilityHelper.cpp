// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/PsychokinesisAbilityHelper.h"

#include "Actor/PsychokineticPropBase.h"
#include "Actor/PsychokineticThrowableProp.h"
#include "Character/Character_Kasane.h"
#include "Components/ComboSystemComponent.h"
#include "Components/PsychokinesisComponent.h"
#include "Components/TargetTrackingSpringArmComponent.h"


void PsychokinesisAbilityHelper::InitComponents(ACharacter_Kasane* Character)
{
	check(Character)
	PsychokinesisComponent = Character->GetPsychokinesisComponent();
	TargetTrackingComponent = Character->GetTargetTrackingComponent();
	ComboSystemComponent = Character->GetComboSystemComponent();
	check(PsychokinesisComponent.IsValid())
	check(TargetTrackingComponent.IsValid())
	check(ComboSystemComponent.IsValid())
}

bool PsychokinesisAbilityHelper::HasPsychokineticPropInRange() const
{
	return PsychokinesisComponent.IsValid() ? PsychokinesisComponent->GetPsychTarget() != nullptr : false;
}

void PsychokinesisAbilityHelper::OnActivatePsychAbility()
{
	if (PsychokinesisComponent.IsValid() && ComboSystemComponent.IsValid())
	{
		CurrentPsychTarget = PsychokinesisComponent->GetPsychTarget();
		PsychokinesisComponent->SetBlockUpdate(true);
		ComboSystemComponent->SetupChargeProperty(CurrentPsychTarget->GetChargeTime(), true);
		ComboSystemComponent->StartCharging();
	}
}

void PsychokinesisAbilityHelper::ActivateThrowPsychAbility()
{
	if (CurrentPsychTarget.IsValid() && TargetTrackingComponent.IsValid())
	{
		auto ThrowableProp = Cast<APsychokineticThrowableProp>(CurrentPsychTarget);
		if (TargetTrackingComponent->GetCurrentTarget())
			ThrowableProp->SetTarget(TargetTrackingComponent->GetCurrentTarget());
		ThrowableProp->Launch();
	}
}

void PsychokinesisAbilityHelper::ActivateSpecialPsychAbility()
{
}
