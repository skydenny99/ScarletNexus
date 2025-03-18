// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_SpecialPsych.h"

#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"
#include "PsychAbilityHelperLibrary.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Components/PsychokinesisComponent.h"


UGameplayEffect* UGA_SpecialPsych::GetCostGameplayEffect() const
{
	check(Kasane);
	UGameplayEffect* CostGameplayEffect = UPsychAbilityHelperLibrary::CreatePsychCostGameplayEffect(Kasane, Kasane->GetPsychokinesisComponent()->GetPsychSpecialTarget());
	return CostGameplayEffect == nullptr ? Super::GetCostGameplayEffect() : CostGameplayEffect;
}

void UGA_SpecialPsych::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	auto ASC = Kasane->GetBaseAbilitySystemComponent();
	if (ASC->TryActivateAbility(Spec.Handle))
	{
		ASC->SetRemoveAbilityOnEnd(Spec.Handle);
	}
		
}
