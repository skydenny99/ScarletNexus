// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BaseType/BaseEnumType.h"
#include "DataAsset_DirectionInputConfig.generated.h"

class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UDataAsset_DirectionInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultInputMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EBaseDirectionType, UInputAction*>	DirectionInputMap;
	
};
