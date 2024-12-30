// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "GA_SASAbilityBase.generated.h"

class UPlayerAttributeSet;
class ACharacter_Kasane;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_SASAbilityBase : public UGameplayAbilityBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	ACharacter_Kasane* Kasane;

	UPROPERTY(EditDefaultsOnly)
	FGameplayAttribute MaxGaugeAttribute;
	UPROPERTY(EditDefaultsOnly)
	float AllowActivateGaugeRate = 0.3f;
	UPROPERTY(EditDefaultsOnly)
	float ReduceGaugeRateOnCancel = 0.1f;

	UPROPERTY()
	UGameplayEffect* GE_ReduceByCancel;

	FGameplayAttribute GetCurrentAttribute() const;
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData = nullptr) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	void OnEndAbility(UGameplayAbility* Ability);
	void ReduceSASGauge();

	UFUNCTION(BlueprintImplementableEvent)
	void InitOnGiveAbility();
};
