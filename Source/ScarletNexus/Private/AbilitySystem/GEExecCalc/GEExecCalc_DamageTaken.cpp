// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "AbilitySystem/Attribute/EnemyAttributeSet.h"
#include "BaseGamePlayTags.h"
#include "BaseDebugHelper.h"



struct FDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Power)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, Attack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, Power, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, DamageTaken, Target, false);
	}
};

static const FDamageCapture& GetDamageCapture()
{
	static FDamageCapture DamageCapture;
	return DamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().AttackDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().PowerDef);
	
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();

	float SourceAttack = 0.f;
	
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().AttackDef, EvaluateParams, SourceAttack);
	Debug::Print(TEXT("SourceAttack"), SourceAttack);

	float BaseDamage = 0.f;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(BaseGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}
	}

	const float FinalDamage = BaseDamage + BaseDamage;
	Debug::Print(TEXT("FinalDamage"), FinalDamage);


	if (FinalDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamage
			)
		);
	}
	
}
