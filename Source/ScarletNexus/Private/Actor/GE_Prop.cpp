// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/GE_Prop.h"

#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"

UGE_Prop::UGE_Prop()
{
	// 이펙트 타입 설정 (즉시 실행)
	DurationPolicy = EGameplayEffectDurationType::Instant;

	// Execution 추가
	FGameplayEffectExecutionDefinition ExecutionDefinition;
	ExecutionDefinition.CalculationClass = UGEExecCalc_DamageTaken::StaticClass();

	Executions.Add(ExecutionDefinition);
	
}
