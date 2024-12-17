// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GA_GroundAttackAbilityBase.h"
#include "GA_GroundBackstep.generated.h"

class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_GroundBackstep : public UGA_GroundAttackAbilityBase
{
	GENERATED_BODY()

protected:
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
};
