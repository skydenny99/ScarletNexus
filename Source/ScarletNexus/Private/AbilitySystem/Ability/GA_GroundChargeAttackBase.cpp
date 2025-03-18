// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_GroundChargeAttackBase.h"

#include "Components/ComboSystemComponent.h"

void UGA_GroundChargeAttackBase::PreActivate(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
	if (ComboSystem)
	{
		ComboSystem->SetupChargeProperty(ChargeTime, false);
		ComboSystem->StartCharging();
		ComboSystem->ResetWeaponCombo();
	}
}
