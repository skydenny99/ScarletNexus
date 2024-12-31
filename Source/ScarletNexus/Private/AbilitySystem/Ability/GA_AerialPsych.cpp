// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_AerialPsych.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BaseGameplayTags.h"
#include "PsychAbilityHelperLibrary.h"
#include "Character/Character_Kasane.h"
#include "Components/ComboSystemComponent.h"
#include "Components/PsychokinesisComponent.h"

void UGA_AerialPsych::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if (Kasane)
	{
		Kasane->MovementModeChangedDelegate.AddDynamic(this, &UGA_AerialPsych::OnGrounded);
	}
}

bool UGA_AerialPsych::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                         const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return CheckCost(Handle, ActorInfo) && ComboSystem->PsychAerialCombo.CurrentComboCount < ComboSystem->PsychAerialCombo.MaxComboCount
		&& UPsychAbilityHelperLibrary::NativeHasPsychokineticThrowablePropInRange(Kasane);
	}
	return false;
}

void UGA_AerialPsych::PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
	UPsychAbilityHelperLibrary::NativeOnActivateNormalPsychAbility(Kasane);
}

void UGA_AerialPsych::OnEndAbility(UGameplayAbility* Ability)
{
	Super::OnEndAbility(Ability);
	Kasane->GetPsychokinesisComponent()->SetBlockUpdate(false);
}

UGameplayEffect* UGA_AerialPsych::GetCostGameplayEffect() const
{
	UGameplayEffect* CostGameplayEffect = UPsychAbilityHelperLibrary::CreatePsychCostGameplayEffect(Kasane);
	return CostGameplayEffect == nullptr ? Super::GetCostGameplayEffect() : CostGameplayEffect;
}


void UGA_AerialPsych::CancelChargingProjectile()
{
	UPsychAbilityHelperLibrary::NativeOnChargingCancelPsychAbility(Kasane);
}

void UGA_AerialPsych::OnGrounded(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	if (PrevMovementMode == MOVE_Falling)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Character, BaseGameplayTags::Shared_Event_Grounded, FGameplayEventData());
	}
}
