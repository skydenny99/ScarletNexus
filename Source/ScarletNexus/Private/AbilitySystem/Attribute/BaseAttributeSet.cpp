// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "GameplayEffectExtension.h"

#include "BaseDebugHelper.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	// Debug::Print(TEXT("Base InitAttribute"));
}

void UBaseAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	
}
