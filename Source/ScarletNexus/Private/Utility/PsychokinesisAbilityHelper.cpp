// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/PsychokinesisAbilityHelper.h"

#include "Actor/PsychokineticPropBase.h"
#include "Actor/PsychokineticThrowableProp.h"
#include "Character/Character_Kasane.h"
#include "Components/ComboSystemComponent.h"
#include "Components/PsychokinesisComponent.h"
#include "Components/TargetTrackingSpringArmComponent.h"


bool FPsychokinesisAbilityHelper::HasPsychokineticPropInRange(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return false;
	const UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	return PsychokinesisComponent ? PsychokinesisComponent->GetPsychTarget() != nullptr : false;
}

void FPsychokinesisAbilityHelper::OnActivatePsychAbility(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	UComboSystemComponent* ComboSystem = Kasane->GetComboSystemComponent();
	if (PsychokinesisComponent && ComboSystem)
	{
		PsychokinesisComponent->SetBlockUpdate(true);
		ComboSystem->SetupChargeProperty(PsychokinesisComponent->GetPsychTarget()->GetChargeTime(), true);
		ComboSystem->StartCharging();
	}
}

void FPsychokinesisAbilityHelper::ActivateThrowPsychAbility(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	UTargetTrackingSpringArmComponent* TargetTracking = Kasane->GetTargetTrackingComponent();
	if (PsychokinesisComponent && TargetTracking)
	{
		const auto ThrowableProp = Cast<APsychokineticThrowableProp>(PsychokinesisComponent->GetPsychTarget());
		if (AActor* Target = TargetTracking->GetCurrentTarget())
		{
			ThrowableProp->SetTargetLocation(Target->GetActorLocation());
		}
		else
		{
			const FVector Forward = Kasane->GetActorForwardVector();
			ThrowableProp->SetTargetLocation(Kasane->GetActorLocation() + Forward * 1000.f);
		}
		ThrowableProp->Launch();
	}
}


void FPsychokinesisAbilityHelper::ActivateSpecialPsychAbility()
{
}
