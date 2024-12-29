// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "Character/Character_Kasane.h"
#include "GA_AttackAbilityBase.generated.h"

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
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void OnEndAbility(UGameplayAbility* Ability);
public:
	
	UFUNCTION(BlueprintPure)
	UAnimInstance* GetKasaneAnimInstance() const {return Kasane->GetMesh()->GetAnimInstance();}
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE UComboSystemComponent* GetComboSystem() const {return ComboSystem;}
};
