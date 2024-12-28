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

bool UBaseAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag Tag)
{
	check(Tag.IsValid());

	TArray<FGameplayAbilitySpec*> AbilitySpecs;
    
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tag.GetSingleTagContainer(), AbilitySpecs);

	if (!AbilitySpecs.IsEmpty())
	{
		const int32 RandomAbilityIndex = FMath::RandRange(0, AbilitySpecs.Num() - 1);
		FGameplayAbilitySpec* AbilitySpec = AbilitySpecs[RandomAbilityIndex];

		check(AbilitySpec);

		if (!AbilitySpec->IsActive())
		{
			return TryActivateAbility(AbilitySpec->Handle);
		}
	}


	return false;
}

bool UBaseAbilitySystemComponent::IsAbilityActive(const FGameplayAbilitySpecHandle& InHandle)
{
	ABILITYLIST_SCOPE_LOCK();
	FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(InHandle);
	return Spec ? Spec->IsActive() : false;
}
