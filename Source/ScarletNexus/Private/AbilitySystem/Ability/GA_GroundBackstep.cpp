// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_GroundBackstep.h"
#include "Components/ComboSystemComponent.h"

bool UGA_GroundBackstep::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return ComboSystem->BackstepGroundCombo.CurrentComboCount < ComboSystem->BackstepGroundCombo.MaxComboCount;
	}
	return false;
}
