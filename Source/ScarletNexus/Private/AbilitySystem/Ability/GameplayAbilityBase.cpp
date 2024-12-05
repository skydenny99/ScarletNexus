// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseDebugHelper.h"

void UGameplayAbilityBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Debug::Print("On Give Ability in AbilityBase");
}

void UGameplayAbilityBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Debug::Print("End Ability in AbilityBase");
}

UBaseAbilitySystemComponent* UGameplayAbilityBase::GetBaseAbilitySystemComponent() const
{
    return Cast<UBaseAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
