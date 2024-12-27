// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "BaseDebugHelper.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	InitCurrentHp(1.f);
	InitMaxHp(1.f);
	InitPower(1.f);
	InitAttack(1.f);
	InitDefence(1.f);
	InitDamageTaken(1.f);
	InitCurrentPsychGauge(1.f);
	InitMaxPsychGauge(1.f);	
	
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
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
		
		const float CashedDefence = GetDefence();
		
		// HP
		const float NewCurrentHp = FMath::Clamp(BeforeHp - (Damage - CashedDefence), 0.0f, GetMaxHp());
		SetCurrentHp(NewCurrentHp);
		
		

		const FString DebugString = FString::Printf(TEXT("Before Hp: %f, Damage: %f, NewCurrentHp : %f"), BeforeHp, Damage, NewCurrentHp);
		Debug::Print(DebugString, FColor::Green);
	}


	


	
	
}
