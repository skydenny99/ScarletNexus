// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_EnemyTakeDamage.h"

#include "AbilitySystem/Attribute/EnemyAttributeSet.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "BaseDebugHelper.h"
#include "BaseGameplayTags.h"


struct FEnemyDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(EnemyAttack)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	FEnemyDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, EnemyAttack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttributeSet, DamageTaken, Target, false);
	}
};
static const FEnemyDamageCapture& GetDamageCapture()
{
	static FEnemyDamageCapture EnemyDamageCapture;
	return EnemyDamageCapture;
}

UGEExecCalc_EnemyTakeDamage::UGEExecCalc_EnemyTakeDamage()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().EnemyAttackDef);
}

void UGEExecCalc_EnemyTakeDamage::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParams.TargetTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();

	float SourceAttack = 0.f;
	
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().EnemyAttackDef, EvaluateParams, SourceAttack);
	Debug::Print(TEXT("Enemy SourceAttack"), SourceAttack);

	float BaseDamage = 0.f;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(BaseGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			Debug::Print(TEXT("Enemy BaseDamage"), BaseDamage);
		}
	}

	const float FinalDamage = SourceAttack + BaseDamage;
	Debug::Print(TEXT("Enemy FinalDamage : SourceAttack + BaseDamage"), FinalDamage);


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
