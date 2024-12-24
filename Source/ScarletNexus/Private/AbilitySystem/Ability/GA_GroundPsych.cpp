// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_GroundPsych.h"

#include "BaseDebugHelper.h"
#include "Character/Character_Kasane.h"
#include "Components/ComboSystemComponent.h"
#include "Components/PsychokinesisComponent.h"
#include "Components/TargetTrackingSpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UGA_GroundPsych::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
}

bool UGA_GroundPsych::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return FPsychokinesisAbilityHelper::HasPsychokineticPropInRange(Kasane);
	}
	return false;
}

void UGA_GroundPsych::PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo,
	FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
	FPsychokinesisAbilityHelper::OnActivatePsychAbility(Kasane);
}

void UGA_GroundPsych::OnEndAbility(UGameplayAbility* Ability)
{
	Super::OnEndAbility(Ability);
	Kasane->GetPsychokinesisComponent()->SetBlockUpdate(false);
}


void UGA_GroundPsych::ThrowProjectile()
{
	FPsychokinesisAbilityHelper::ActivateThrowPsychAbility(Kasane);
}

EPsychType UGA_GroundPsych::GetPsychType()
{
	return static_cast<EPsychType>(UKismetMathLibrary::RandomIntegerInRange(0, 5));
}
