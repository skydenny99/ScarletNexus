// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GA_GroundAttackAbilityBase.h"
#include "GA_SpecialPsych.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_SpecialPsych : public UGA_GroundAttackAbilityBase
{
	GENERATED_BODY()

protected:
	virtual UGameplayEffect* GetCostGameplayEffect() const override;
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
