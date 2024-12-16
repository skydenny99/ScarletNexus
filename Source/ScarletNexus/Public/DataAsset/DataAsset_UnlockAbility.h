// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "Engine/DataAsset.h"
#include "DataAsset_UnlockAbility.generated.h"

USTRUCT(BlueprintType)
struct FUnlockData
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category = "Unlock", meta = (Categories = "Unlock"))
	FGameplayTag UnlockTag;

	UPROPERTY(EditDefaultsOnly, Category = "Unlock", meta = (Categories = "InputTag"))
	FGameplayTag OverrideInputTag;

	UPROPERTY(EditDefaultsOnly, Category = "Unlock")
	TSubclassOf<UGameplayAbilityBase> OverrideAbility;
	
	UPROPERTY(EditDefaultsOnly, Category = "Unlock")
	int32 Level = 1;

	FORCEINLINE bool IsValid() const
	{
		return UnlockTag.IsValid() && OverrideInputTag.IsValid() && OverrideAbility;
	}
};

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UDataAsset_UnlockAbility : public UDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Startup", meta = (Categories = "Unlock"))
	TArray<FUnlockData> UnlockDatas;
public:
	bool FindUnlockDataByTag(FGameplayTag UnlockTag, FUnlockData& OutUnlockData);
};
