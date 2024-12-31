// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_SpecialPsych.h"
#include "PsychAbilityHelperLibrary.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Components/PsychokinesisComponent.h"



bool UGA_SpecialPsych::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                          const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return CheckCost(Handle, ActorInfo) && UPsychAbilityHelperLibrary::NativeHasPsychokineticSpecialPropInRange(Kasane);
	}
	return false;
}

void UGA_SpecialPsych::PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
	UPsychAbilityHelperLibrary::NativeOnActivateSpecialPsychAbility(Kasane);
}

void UGA_SpecialPsych::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

UGameplayEffect* UGA_SpecialPsych::GetCostGameplayEffect() const
{
	check(Kasane);
	UGameplayEffect* CostGameplayEffect = UPsychAbilityHelperLibrary::CreatePsychCostGameplayEffect(Kasane, Kasane->GetPsychokinesisComponent()->GetPsychSpecialTarget());
	return CostGameplayEffect == nullptr ? Super::GetCostGameplayEffect() : CostGameplayEffect;
}

void UGA_SpecialPsych::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	Kasane = Cast<ACharacter_Kasane>(ActorInfo->AvatarActor);
	if (Kasane->GetBaseAbilitySystemComponent()->TryActivateAbility(Spec.Handle) == false)
		Debug::Print("Ability Activation Failure");
		
}
