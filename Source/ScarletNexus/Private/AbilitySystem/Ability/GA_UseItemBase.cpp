// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_UseItemBase.h"

#include "Character/Character_Kasane.h"

void UGA_UseItemBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	ACharacter_Kasane* Kasane = Cast<ACharacter_Kasane>(ActorInfo->AvatarActor);
	check(Kasane);
	InventoryComponent = Kasane->GetInventoryComponent();
}

bool UGA_UseItemBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                         const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		
	}
	return false;
}
