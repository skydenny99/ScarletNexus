// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GA_DodgeBase.h"
#include "GA_Dodge_Player.generated.h"

class UKasaneAnimInstance;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_Dodge_Player : public UGA_DodgeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	UKasaneAnimInstance* KasaneAnimInstance;
	UPROPERTY()
	UCharacterMovementComponent* DodgeMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="Dodge")
	int32 DodgeCount = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Dodge")
	int32 MaxDodgeCount;

public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void GetCharacterDodgeDirection(EBaseDirectionType& DirectionResult) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	void PlayDodgeAnimation(EBaseDirectionType Direction);
	
	UFUNCTION(BlueprintCallable)
	void OnEndDodge();

	void OnCancelDodge();

	UFUNCTION()
	void ResetDodgeCount(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);
};
