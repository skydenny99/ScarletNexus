// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_AerialPsych.h"

#include "Character/Character_Kasane.h"
#include "Components/ComboSystemComponent.h"
#include "Components/PsychokinesisComponent.h"
#include "Utility/PsychokinesisAbilityHelper.h"

bool UGA_AerialPsych::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return ComboSystem->PsychAerialCombo.CurrentComboCount < ComboSystem->PsychAerialCombo.MaxComboCount && FPsychokinesisAbilityHelper::HasPsychokineticPropInRange(Kasane);
	}
	return false;
}

void UGA_AerialPsych::PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
	FPsychokinesisAbilityHelper::OnActivatePsychAbility(Kasane);
}

void UGA_AerialPsych::OnEndAbility(UGameplayAbility* Ability)
{
	Super::OnEndAbility(Ability);
	Kasane->GetPsychokinesisComponent()->SetBlockUpdate(false);
}

void UGA_AerialPsych::ThrowProjectile()
{
	FPsychokinesisAbilityHelper::ActivateThrowPsychAbility(Kasane);
}

void UGA_AerialPsych::CancelChargingProjectile()
{
	FPsychokinesisAbilityHelper::OnChargingCancelPsychAbility(Kasane);
}
