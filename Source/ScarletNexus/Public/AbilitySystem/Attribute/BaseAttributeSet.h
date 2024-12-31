// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"

#include "BaseAttributeSet.generated.h"


class IPawnUIInterface;
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPercentChangeDelegate, float, NewPercent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueChangeDelegate, float, NewValue);

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

	// 델리게이트
	// HP
	//UPROPERTY(BlueprintAssignable)
	//FOnPercentChangeDelegate OnCurrentHpPercentChanged;

	//UPROPERTY(BlueprintAssignable)
	//FOnValueChangeDelegate OnCurrentHpValueChanged;

	// BrainCrush Gauge
	//UPROPERTY(BlueprintAssignable)
	//FOnPercentChangeDelegate OnCurrentBrainCrushGaugePercentChanged;
	
	//UPROPERTY(BlueprintAssignable)
	//FOnValueChangeDelegate OnCurrentBrainCrushGaugeValueChanged;

protected:
	TWeakInterfacePtr<IPawnUIInterface> CachedUIInterface;
	
};
