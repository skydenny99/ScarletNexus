// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_SpecialPsychEntry.h"

#include "BaseDebugHelper.h"
#include "PsychAbilityHelperLibrary.h"

bool UGA_SpecialPsychEntry::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                               const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                               const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		//if (UPsychAbilityHelperLibrary::NativeHasPsychokineticSpecialPropInRange(Kasane) == false)
			//Debug::Print("PsychokineticSpecialPropInRange No Prop");
		return CheckCost(Handle, ActorInfo) && UPsychAbilityHelperLibrary::NativeHasPsychokineticSpecialPropInRange(Kasane);
	}
	//Debug::Print("UGA_SpecialPsychEntry::CanActivateAbility Failed super");
	return false;
}

void UGA_SpecialPsychEntry::PreActivate(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
	UPsychAbilityHelperLibrary::NativeOnActivateSpecialPsychAbility(Kasane);
}

void UGA_SpecialPsychEntry::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
	UPsychAbilityHelperLibrary::ActivateSpecialPsychAbility(Kasane);
}
