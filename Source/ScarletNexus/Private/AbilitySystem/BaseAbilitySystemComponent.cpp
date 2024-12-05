// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAbilitySystemComponent.h"

void UBaseAbilitySystemComponent::OnAbilityInputTriggered(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid() == false) return;
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (Spec.DynamicAbilityTags.HasTagExact(InputTag) == false) continue;
		TryActivateAbility(Spec.Handle);
	}
}
