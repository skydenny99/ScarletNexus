// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "DataAsset_StartupKasane.generated.h"

class UGameplayAbilityBase;

USTRUCT(BlueprintType)
struct FInputBindData
{

	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	//부여가능한 능력
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbilityBase> AbilityToGrant;
	FORCEINLINE bool IsValid() const
	{
		return InputTag.IsValid() && AbilityToGrant;;
	}
};

USTRUCT(BlueprintType)
struct FUnlockData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Unlock", meta = (Categories = "InputTag"))
	FGameplayTag OverrideTargetTag;

	UPROPERTY(EditDefaultsOnly, Category = "Unlock")
	TSubclassOf<UGameplayAbilityBase> OverrideAbility;

	FORCEINLINE bool IsValid() const
	{
		return OverrideTargetTag.IsValid() && OverrideAbility;
	}
};

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UDataAsset_StartupKasane : public UDataAsset_StartupBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Startup", meta = (Categories = "Unlock"))
	FGameplayTagContainer UnlockTags;

	UPROPERTY(EditDefaultsOnly, Category = "Startup", meta = (Categories = "Unlock"))
	TMap<FGameplayTag, FUnlockData> UnlockDatas;

	UPROPERTY(EditDefaultsOnly, Category = "Startup")
	TArray<FInputBindData> HeroStartupAbilitySets;

public:
	virtual void GiveStartupAbilities(UAbilitySystemComponent* ASC, int32 Level = 1) override;

protected:

	void GiveUnlockAbilities(UAbilitySystemComponent* ASC, int32 Level = 1);
};
