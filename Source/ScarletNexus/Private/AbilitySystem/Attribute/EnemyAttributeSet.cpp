// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/EnemyAttributeSet.h"
#include "GameplayEffectExtension.h"
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
	InitDamageTaken(1.f);

	Debug::Print(TEXT("Enemy InitAttribute"));
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetCurrentHpAttribute())
	{
		const float NewCurrentHp = FMath::Clamp(GetCurrentHp(), 0.0f, GetMaxHp());
		SetCurrentHp(NewCurrentHp);
	}
	

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float BeforeHp = GetCurrentHp();
		const float Damage = GetDamageTaken();

		const float NewCurrentHp = FMath::Clamp(BeforeHp - Damage, 0.0f, GetMaxHp());
		SetCurrentHp(NewCurrentHp);

		const FString DebugString = FString::Printf(TEXT("Before Hp: %f, Damage: %f, NewCurrentHp : %f"), BeforeHp, Damage, NewCurrentHp);
		Debug::Print(DebugString, FColor::Green);
	}
	
}
