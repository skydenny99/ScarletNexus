// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_UseItemBase.h"

#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "Character/Character_Kasane.h"
#include "Components/InventoryComponent.h"

void UGA_UseItemBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	Kasane = Cast<ACharacter_Kasane>(ActorInfo->AvatarActor);
	check(Kasane);
	InventoryComponent = Kasane->GetInventoryComponent();
	check(InventoryComponent);
}

bool UGA_UseItemBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                         const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                         const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return InventoryComponent->CanUseItem() && UBaseFunctionLibrary::NativeActorHasTag(Kasane, InventoryComponent->GetCurrentSelectedItemInfo().CooldownTag) == false;
	}
	return false;
}

void UGA_UseItemBase::UseCurrentSelectedItem()
{
	if (InventoryComponent)
	{
		InventoryComponent->UseCurrentSelectedItem(Kasane);
	}
}
