// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExCalc_PsychoDamage.h"

#include "AbilitySystem/Attribute/EnemyAttributeSet.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "BaseDebugHelper.h"
#include "BaseGameplayTags.h"

struct FPsychoDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Power)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FPsychoDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, Attack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, Power, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, DamageTaken, Target, false);
	}
};

static const FPsychoDamageCapture& GetPsychoDamageCapture()
{
	static FPsychoDamageCapture PsychoDamageCapture;
	return PsychoDamageCapture;
}



UGEExCalc_PsychoDamage::UGEExCalc_PsychoDamage()
{
	RelevantAttributesToCapture.Add(GetPsychoDamageCapture().AttackDef);
	RelevantAttributesToCapture.Add(GetPsychoDamageCapture().PowerDef);
}

void UGEExCalc_PsychoDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();

	float SourceAttack = 0.f;
	
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetPsychoDamageCapture().AttackDef, EvaluateParams, SourceAttack);
	Debug::Print(TEXT("SourceAttack"), SourceAttack);

	float SourcePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetPsychoDamageCapture().PowerDef, EvaluateParams, SourcePower);
	Debug::Print(TEXT("SourcePower"), SourcePower);

	float BaseDamage = 0.f;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(BaseGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			Debug::Print(TEXT("BaseDamage"), BaseDamage);
		}
	}
	const float FinalDamage = SourceAttack + BaseDamage + SourcePower;
	Debug::Print(TEXT("FinalDamage"), FinalDamage);


	if (FinalDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetPsychoDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamage
			)
		);
	}
	
}
