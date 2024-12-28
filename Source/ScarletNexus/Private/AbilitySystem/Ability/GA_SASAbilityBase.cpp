// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_SASAbilityBase.h"

#include "BaseFunctionLibrary.h"
#include "Character/Character_Kasane.h"

void UGA_SASAbilityBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	Kasane = Cast<ACharacter_Kasane>(ActorInfo->AvatarActor);
	check(Kasane);
}

void UGA_SASAbilityBase::PreActivate(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData)
{
	Super::PreActivate(Handle, ActorInfo, ActivationInfo, OnGameplayAbilityEndedDelegate, TriggerEventData);
	UBaseFunctionLibrary::AddPlaygameTagToActor(Kasane, AbilityTags.First());
}

void UGA_SASAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                         const FGameplayEventData* TriggerEventData)
{
	OnGameplayAbilityEnded.AddUObject(this, &UGA_SASAbilityBase::OnEndAbility);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGA_SASAbilityBase::OnEndAbility(UGameplayAbility* Ability)
{
	UBaseFunctionLibrary::RemovePlayGameTagFromActor(Kasane, AbilityTags.First());
}
