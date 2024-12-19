// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "FellowCharacterGameplayAbility.generated.h"


class AFellowCharacter;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UFellowCharacterGameplayAbility : public UGameplayAbilityBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Ability")
	AFellowCharacter* GetFellowCharacterFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Ability")
	FGameplayEffectSpecHandle MakeFellowDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> Effect, const FScalableFloat& DamageFloat);

private:
	TWeakObjectPtr<AFellowCharacter> CachedFellowCharacter;
	
};
