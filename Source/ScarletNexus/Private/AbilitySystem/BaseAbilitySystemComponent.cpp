// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseDebugHelper.h"

void UBaseAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
}

void UBaseAbilitySystemComponent::OnAbilityInputTriggered(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid() == false) return;
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if(Spec.Ability.Get()->AbilityTags.HasTag(InputTag) == false) continue;
		TryActivateAbility(Spec.Handle);
	}
}
