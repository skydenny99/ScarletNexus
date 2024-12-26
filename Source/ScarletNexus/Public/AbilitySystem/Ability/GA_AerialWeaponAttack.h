// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GA_AerialAttackAbilityBase.h"
#include "GA_AerialWeaponAttack.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_AerialWeaponAttack : public UGA_AerialAttackAbilityBase
{
	GENERATED_BODY()

protected:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	
};
