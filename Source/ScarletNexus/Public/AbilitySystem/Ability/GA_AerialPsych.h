// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GA_AerialAttackAbilityBase.h"
#include "Character/Character_Kasane.h"
#include "GA_AerialPsych.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_AerialPsych : public UGA_AerialAttackAbilityBase
{
	GENERATED_BODY()
protected:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData = nullptr) override;
	virtual void OnEndAbility(UGameplayAbility* Ability) override;
	virtual UGameplayEffect* GetCostGameplayEffect() const override;
	
};
