// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "PlayerAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UPlayerAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()
	public:
	UPlayerAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData CurrentHp;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, CurrentHp)

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData MaxHp;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxHp)

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData Power;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Power)

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Attack)

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData Defence;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Defence)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, DamageTaken)

	// 카사네꺼 확장 
	// 염동력 게이지

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData CurrentPsychGauge;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, CurrentPsychGauge)

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData MaxPsychGauge;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaxPsychGauge)

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	float GetCurrentPsychGaugeBP() const { return GetCurrentPsychGauge(); }

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void SetCurrentPsychGaugeBP(float NewValue) {SetCurrentPsychGauge(NewValue);}

	
	
};
