// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_AttackAbilityBase.h"

#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"
#include "Components/ComboSystemComponent.h"

void UGA_AttackAbilityBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	Kasane = Cast<ACharacter_Kasane>(ActorInfo->AvatarActor);
	check(Kasane);
	ComboSystem = Kasane->GetComboSystemComponent();
	check(ComboSystem);
}

bool UGA_AttackAbilityBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Shared_Status_CanAttack);
	}
	return false;
}

void UGA_AttackAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	OnGameplayAbilityEnded.AddUObject(this, &UGA_AttackAbilityBase::OnEndAbility);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UBaseFunctionLibrary::RemovePlayGameTagFromActor(Kasane, BaseGameplayTags::Shared_Status_CanAttack);
	UBaseFunctionLibrary::RemovePlayGameTagFromActor(Kasane, BaseGameplayTags::Shared_Status_CanMove);
}

void UGA_AttackAbilityBase::OnEndAbility(UGameplayAbility* Ability)
{
	if (ComboSystem)
	{
		ComboSystem->ResetActivateAbilityTag();
	}
	UBaseFunctionLibrary::AddPlaygameTagToActor(Kasane, BaseGameplayTags::Shared_Status_CanAttack);
	UBaseFunctionLibrary::AddPlaygameTagToActor(Kasane, BaseGameplayTags::Shared_Status_CanMove);
	Debug::Print("Ability End");
}


