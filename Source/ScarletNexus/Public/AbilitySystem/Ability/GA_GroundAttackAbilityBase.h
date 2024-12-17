// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GA_AttackAbilityBase.h"
#include "GA_GroundAttackAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_GroundAttackAbilityBase : public UGA_AttackAbilityBase
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
