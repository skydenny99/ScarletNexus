// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/EnemyAttributeSet.h"
#include "BaseDebugHelper.h"

UEnemyAttributeSet::UEnemyAttributeSet()
{
	
	InitCurrentHp(1.f);
	InitMaxHp(1.f);
	InitCurrentDownGauge(1.f);
	InitMaxDownGauge(1.f);
	InitCurrentBrainCrushGauge(1.f);
	InitMaxBrainCrushGauge(1.f);
	InitEnemyAttack(1.f);

	Debug::Print(TEXT("Enemy InitAttribute"));
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	
}
