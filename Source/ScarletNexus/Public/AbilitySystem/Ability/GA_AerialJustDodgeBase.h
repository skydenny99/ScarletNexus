// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GA_AerialAttackAbilityBase.h"
#include "Character/Character_Kasane.h"
#include "GA_AerialJustDodgeBase.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_AerialJustDodgeBase : public UGA_AerialAttackAbilityBase
{
	GENERATED_BODY()

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	UFUNCTION()
	void OnGrounded(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);
};
