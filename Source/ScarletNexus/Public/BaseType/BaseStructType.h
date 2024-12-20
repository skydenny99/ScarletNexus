// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class SCARLETNEXUS_API BaseStructType
{
public:
	BaseStructType();
	~BaseStructType();
};

UENUM(BlueprintType)
enum class EBaseAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

