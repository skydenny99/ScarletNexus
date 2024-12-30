// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExCalc_PsychoDamage.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGEExCalc_PsychoDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UGEExCalc_PsychoDamage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
