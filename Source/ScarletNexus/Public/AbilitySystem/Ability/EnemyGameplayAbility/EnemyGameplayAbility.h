// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "EnemyGameplayAbility.generated.h"

class ABaseEnemyCharacter;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UEnemyGameplayAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()

	public:
	UFUNCTION(BlueprintPure, Category = "Ability")
	ABaseEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, const FScalableFloat& DamageFloat);
	
	

	private:
	TWeakObjectPtr<ABaseEnemyCharacter> CachedEnemyCharacter;
	
};
