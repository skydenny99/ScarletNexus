// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GA_AttackAbilityBase.h"
#include "GA_AerialAttackAbilityBase.generated.h"

class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_AerialAttackAbilityBase : public UGA_AttackAbilityBase
{
	GENERATED_BODY()
	

protected:
	float OriginGravityScale;
	UPROPERTY()
	UCharacterMovementComponent* MovementComponent;
	
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	void OnEndAerialAbility(UGameplayAbility* ability);
};
