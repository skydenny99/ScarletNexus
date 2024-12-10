// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_DodgeBase.h"
#include "Animation/AnimMontage.h"
#include "BaseType/BaseEnumType.h"
#include "Character/BaseCharacter.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"

void UGA_DodgeBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	DodgeCharacter = GetOwnerWithCasting<ABaseCharacter>();
}

bool UGA_DodgeBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{

	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		return UBaseFunctionLibrary::NativeActorHasAnyTags(DodgeCharacter, BlockDodgeTags) == false;
	}
	return false;
}

void UGA_DodgeBase::GetCharacterDodgeDirection(EBaseDirectionType& DirectionResult)
{
	DirectionResult = EBaseDirectionType::None;
}
