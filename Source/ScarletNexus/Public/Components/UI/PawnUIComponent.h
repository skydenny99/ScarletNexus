// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseType/BaseEnumType.h"
#include "Components/PawnExtensionComponent.h"
#include "Basetype/BaseStructType.h"
#include "PawnUIComponent.generated.h"

//Player,Enemy
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangeDelegate, float, NewPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDebuffChangeDelegate, EBaseDebuffType, NewDebuff);

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UPawnUIComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()

public:
	//Player,Enemy
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnCurrentHpChanged;

	UPROPERTY(BlueprintAssignable)
	FDebuffChangeDelegate OnDebuffChanged;
};