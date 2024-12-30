// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_GroundPsych.h"

#include "PsychAbilityHelperLibrary.h"
#include "Character/Character_Kasane.h"
#include "Components/ComboSystemComponent.h"
#include "Components/PsychokinesisComponent.h"


void UGA_GroundPsych::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	Debug::Print(FString::Printf(TEXT("Character Given Name: %s"), *ActorInfo->AvatarActor->GetActorLabel()));
}

bool UGA_GroundPsych::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                         const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return CheckCost(Handle, ActorInfo) && UPsychAbilityHelperLibrary::NativeHasPsychokineticPropInRange(Kasane);
	}
	return false;
}

void UGA_GroundPsych::PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
	ComboSystem->ClearPsychComboTimer();
	UPsychAbilityHelperLibrary::NativeOnActivatePsychAbility(Kasane);
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
	UGameplayEffect* CostGameplayEffect = UPsychAbilityHelperLibrary::CreatePsychCostGameplayEffect(Kasane);
	return CostGameplayEffect == nullptr ? Super::GetCostGameplayEffect() : CostGameplayEffect;
}

void UGA_GroundPsych::CancelChargingProjectile()
{
	UPsychAbilityHelperLibrary::NativeOnChargingCancelPsychAbility(Kasane);
}
