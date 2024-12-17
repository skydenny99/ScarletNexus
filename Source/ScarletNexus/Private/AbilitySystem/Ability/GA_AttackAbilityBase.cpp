// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_AttackAbilityBase.h"

#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"
#include "Character/Character_Kasane.h"

void UGA_AttackAbilityBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	Kasane = Cast<ACharacter_Kasane>(ActorInfo->AvatarActor);
	check(Kasane);
	ComboSystem = Kasane->GetComboSystemComponent();
	check(ComboSystem);
	OnGameplayAbilityCancelled.AddLambda([ActorInfo]()
	{
		if (ActorInfo->AvatarActor.IsValid() == false) return;
		UBaseFunctionLibrary::AddPlaygameTagToActor(ActorInfo->AvatarActor.Get(), BaseGameplayTags::Shared_Status_CanAttack);
		UBaseFunctionLibrary::AddPlaygameTagToActor(ActorInfo->AvatarActor.Get(), BaseGameplayTags::Shared_Status_CanMove);
	});
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
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UBaseFunctionLibrary::RemovePlayGameTagFromActor(Kasane, BaseGameplayTags::Shared_Status_CanAttack);
	UBaseFunctionLibrary::RemovePlayGameTagFromActor(Kasane, BaseGameplayTags::Shared_Status_CanMove);
}


