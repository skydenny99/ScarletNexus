// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/FellowCharacterGameplayAbility/FellowCharacterGameplayAbility.h"
#include "Character/FellowCharacter.h"
#include "BaseGameplayTags.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"

AFellowCharacter* UFellowCharacterGameplayAbility::GetFellowCharacterFromActorInfo()
{
	if (!CachedFellowCharacter.IsValid())
	{
		CachedFellowCharacter = Cast<AFellowCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedFellowCharacter.IsValid() ? CachedFellowCharacter.Get() : nullptr;
}

FGameplayEffectSpecHandle UFellowCharacterGameplayAbility::MakeFellowDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> Effect, const FScalableFloat& DamageFloat)
{
	check(Effect);

	FGameplayEffectContextHandle ContextHandle;
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle SpecHandle = GetBaseAbilitySystemComponent()->MakeOutgoingSpec(
		Effect,
		GetAbilityLevel(),
		ContextHandle
	);
	
	SpecHandle.Data->SetSetByCallerMagnitude(BaseGameplayTags::Shared_SetByCaller_BaseDamage,DamageFloat.GetValueAtLevel(GetAbilityLevel()));
	return SpecHandle;
	
}
