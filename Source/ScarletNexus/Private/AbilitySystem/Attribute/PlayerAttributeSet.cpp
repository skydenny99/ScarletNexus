// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/PlayerAttributeSet.h"

#include "BaseDebugHelper.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	InitCurrentHp(1.f);
	InitMaxHp(1.f);
	InitPower(1.f);
	InitAttack(1.f);
	InitDefence(1.f);
	InitDamageTaken(1.f);
	
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	// Super::PostGameplayEffectExecute(Data);


	
	
}
