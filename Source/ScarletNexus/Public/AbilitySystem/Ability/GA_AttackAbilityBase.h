// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "GA_AttackAbilityBase.generated.h"

class ACharacter_Kasane;
class UComboSystemComponent;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_AttackAbilityBase : public UGameplayAbilityBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	ACharacter_Kasane* Kasane;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UComboSystemComponent* ComboSystem;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
public:

	UFUNCTION(BlueprintPure)
	FORCEINLINE ACharacter_Kasane* GetKasane() { return Kasane; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE UComboSystemComponent* GetComboSystem() const {return ComboSystem;}
};
