// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExecCalc_EnemyTakeDamage.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGEExecCalc_EnemyTakeDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	public:
	UGEExecCalc_EnemyTakeDamage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
	
};
