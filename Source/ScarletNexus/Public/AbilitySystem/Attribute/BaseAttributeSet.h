// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"

#include "BaseAttributeSet.generated.h"



/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	public:
	UBaseAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	
	
};
