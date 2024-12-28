// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GA_SASAbilityBase.h"
#include "Engine/DataAsset.h"
#include "DataAsset_SASAbility.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UDataAsset_SASAbility : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	TArray<TSubclassOf<UGA_SASAbilityBase>> SASAbilityList;
};
