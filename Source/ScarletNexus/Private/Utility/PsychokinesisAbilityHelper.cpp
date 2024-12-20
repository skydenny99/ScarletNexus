// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/PsychokinesisAbilityHelper.h"

#include "Actor/PsychokineticPropBase.h"
#include "Character/Character_Kasane.h"
#include "Components/ComboSystemComponent.h"
#include "Components/PsychokinesisComponent.h"


void PsychokinesisAbilityHelper::InitComponents(ACharacter_Kasane* Character)
{
	check(Character)
	PsychokinesisComponent = Character->GetPsychokinesisComponent();
	TargetTrackingComponent = Character->GetTargetTrackingComponent();
	check(PsychokinesisComponent)
	check(TargetTrackingComponent)
}

bool PsychokinesisAbilityHelper::HasPsychokineticPropInRange() const
{
	return PsychokinesisComponent->GetPsychTarget() != nullptr;
}

void PsychokinesisAbilityHelper::OnActivatePsychAbility()
{
	CurrentPsychTarget = PsychokinesisComponent->GetPsychTarget();
	ComboSystemComponent->SetupChargeProperty(CurrentPsychTarget->GetChargeTime(), true);
	ComboSystemComponent->StartCharging();
}

void PsychokinesisAbilityHelper::ActivateThrowPsychAbility()
{
}

void PsychokinesisAbilityHelper::ActivateSpecialPsychAbility()
{
}
