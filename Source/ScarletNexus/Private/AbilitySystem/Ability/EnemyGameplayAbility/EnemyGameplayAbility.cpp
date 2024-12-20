// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/EnemyGameplayAbility/EnemyGameplayAbility.h"
#include "Character/EnemyCharacter/BaseEnemyCharacter.h"
#include "BaseGameplayTags.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"

ABaseEnemyCharacter* UEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<ABaseEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
	
}

FGameplayEffectSpecHandle UEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect,
	const FScalableFloat& DamageFloat)
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
