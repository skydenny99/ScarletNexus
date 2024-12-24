// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GA_GroundAttackAbilityBase.h"
#include "Character/Character_Kasane.h"
#include "Components/PsychokinesisComponent.h"
#include "Utility/PsychokinesisAbilityHelper.h"
#include "GA_GroundPsych.generated.h"

class UPsychokinesisComponent;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_GroundPsych : public UGA_GroundAttackAbilityBase, public PsychokinesisAbilityHelper
{
	GENERATED_BODY()

protected:
	
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData = nullptr) override;
	virtual void OnEndAbility(UGameplayAbility* Ability) override;
	
	UFUNCTION(BlueprintCallable)
	void ThrowProjectile();

	UFUNCTION(BlueprintPure)
	UAnimInstance* GetKasaneAnimInstance() const {return Kasane->GetMesh()->GetAnimInstance();}

	UFUNCTION(BlueprintPure)
	EPsychType GetPsychType();

};
