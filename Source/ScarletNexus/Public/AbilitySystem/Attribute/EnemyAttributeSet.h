// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "EnemyAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UEnemyAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

	public:
	UEnemyAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData CurrentHp;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, CurrentHp)

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData MaxHp;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MaxHp)

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData CurrentDownGauge;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, CurrentDownGauge)

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData MaxDownGauge;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MaxDownGauge)

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ResetDownGaugeBP() { SetCurrentDownGauge(GetMaxDownGauge()); }

	UPROPERTY(BlueprintReadOnly, Category="Status")
	FGameplayAttributeData CurrentBrainCrushGauge;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, CurrentBrainCrushGauge)

	UPROPERTY(BlueprintReadOnly, Category = "Status")
	FGameplayAttributeData MaxBrainCrushGauge;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, MaxBrainCrushGauge)

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ResetBrainCrushGaugeBP() { SetCurrentBrainCrushGauge(GetMaxBrainCrushGauge()); }
	
	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData EnemyAttack;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, EnemyAttack)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UEnemyAttributeSet, DamageTaken)


	
};
