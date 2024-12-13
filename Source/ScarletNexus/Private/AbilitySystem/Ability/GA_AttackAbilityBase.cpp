// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_AttackAbilityBase.h"

#include "Character/Character_Kasane.h"

void UGA_AttackAbilityBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	Kasane = Cast<ACharacter_Kasane>(ActorInfo->AvatarActor);
	check(Kasane);
	ComboSystem = Kasane->GetComboSystemComponent();
	check(ComboSystem);
}


