// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "DataAsset_StartupFellow.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UDataAsset_StartupFellow : public UDataAsset_StartupBase
{
	GENERATED_BODY()

public:
	virtual void GiveStartupAbilities(UAbilitySystemComponent* ASC, int32 Level = 1) override;

	
	
};
