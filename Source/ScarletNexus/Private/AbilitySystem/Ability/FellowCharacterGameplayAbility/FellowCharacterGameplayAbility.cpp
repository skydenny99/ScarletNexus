// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/FellowCharacterGameplayAbility/FellowCharacterGameplayAbility.h"
#include "Character/FellowCharacter.h"

AFellowCharacter* UFellowCharacterGameplayAbility::GetFellowCharacterFromActorInfo()
{
	if (!CachedFellowCharacter.IsValid())
	{
		CachedFellowCharacter = Cast<AFellowCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedFellowCharacter.IsValid() ? CachedFellowCharacter.Get() : nullptr;
}
