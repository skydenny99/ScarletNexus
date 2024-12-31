// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_GroundPsych.h"

#include "PsychAbilityHelperLibrary.h"
#include "Character/Character_Kasane.h"
#include "Components/ComboSystemComponent.h"
#include "Components/PsychokinesisComponent.h"


bool UGA_GroundPsych::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                         const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return CheckCost(Handle, ActorInfo) && UPsychAbilityHelperLibrary::NativeHasPsychokineticThrowablePropInRange(Kasane);
	}
	return false;
}

void UGA_GroundPsych::PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
	ComboSystem->ClearPsychComboTimer();
	UPsychAbilityHelperLibrary::NativeOnActivateNormalPsychAbility(Kasane);
}

void UGA_GroundPsych::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbilityCost(Handle, ActorInfo, ActivationInfo))
	{			
		constexpr bool bReplicateEndAbility = true;
		constexpr bool bWasCancelled = true;
		EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGA_GroundPsych::OnEndAbility(UGameplayAbility* Ability)
{
	Super::OnEndAbility(Ability);
	Kasane->GetPsychokinesisComponent()->SetBlockUpdate(false);
}

UGameplayEffect* UGA_GroundPsych::GetCostGameplayEffect() const
{
	UGameplayEffect* CostGameplayEffect = UPsychAbilityHelperLibrary::CreatePsychCostGameplayEffect(Kasane, Kasane->GetPsychokinesisComponent()->GetPsychThrowableTarget());
	return CostGameplayEffect == nullptr ? Super::GetCostGameplayEffect() : CostGameplayEffect;
}
