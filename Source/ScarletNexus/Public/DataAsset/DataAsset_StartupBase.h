// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "DataAsset_StartupBase.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UDataAsset_StartupBase : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Startup")
	TArray<TSubclassOf<UGameplayAbilityBase>> StartupAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Startup")
	TArray<TSubclassOf<UGameplayEffect>> StartupGameplayEffects;
	


public:
	virtual void GiveStartupAbilities(UAbilitySystemComponent* ASC, int32 Level = 1);
};
