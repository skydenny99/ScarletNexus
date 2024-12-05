// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseDebugHelper.h"

void UBaseAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{

}

void UBaseAbilitySystemComponent::OnAbilityInputTriggered(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid() == false) return;
	for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		Debug::Print("Input Triggered");
		if(Spec.Ability.Get()->AbilityTags.HasTag(InputTag) == false) continue;
		Debug::Print("Input Triggered");
		TryActivateAbility(Spec.Handle);
	}
}
