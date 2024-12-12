// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/EnemyGameplayAbility/EnemyGameplayAbility.h"
#include "Character/EnemyCharacter/BaseEnemyCharacter.h"

ABaseEnemyCharacter* UEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedEnemyCharacter.IsValid())
	{
		CachedEnemyCharacter = Cast<ABaseEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
	
}
