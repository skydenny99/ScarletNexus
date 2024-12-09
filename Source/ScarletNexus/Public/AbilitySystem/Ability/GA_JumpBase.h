// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "GA_JumpBase.generated.h"

class UCharacterMovementComponent;
class ACharacter_Kasane;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_JumpBase : public UGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	UCharacterMovementComponent* MovementComponent;
	ACharacter_Kasane* Kasane;

	UPROPERTY(EditDefaultsOnly, Category = "Jumping")
	TArray<int32> JumpPower;

	FTimerHandle ResetJumpTimer;

public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

};
