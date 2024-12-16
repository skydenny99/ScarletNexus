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

	//�ο������� �ɷ�
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayAbilityBase> AbilityToGrant;
	FORCEINLINE bool IsValid() const
	{
		return InputTag.IsValid() && AbilityToGrant;;
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

public:
	virtual void GiveStartupAbilities(UAbilitySystemComponent* ASC, int32 Level = 1) override;

protected:

	void GiveUnlockAbilities(UAbilitySystemComponent* ASC);
};
