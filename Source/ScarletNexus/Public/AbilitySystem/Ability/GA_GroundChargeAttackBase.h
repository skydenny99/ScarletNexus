// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GA_GroundAttackAbilityBase.h"
#include "GA_GroundChargeAttackBase.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_GroundChargeAttackBase : public UGA_GroundAttackAbilityBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Charge")
	float ChargeTime = 1.f;
	virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData = nullptr) override;
};
