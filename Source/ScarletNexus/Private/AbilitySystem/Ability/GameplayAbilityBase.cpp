// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "BaseDebugHelper.h"



UBaseAbilitySystemComponent* UGameplayAbilityBase::GetBaseAbilitySystemComponent() const
{
    return Cast<UBaseAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

UPawnCombatComponent* UGameplayAbilityBase::GetPawnCombatComponentFromActorInfo() const
{
    return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}
