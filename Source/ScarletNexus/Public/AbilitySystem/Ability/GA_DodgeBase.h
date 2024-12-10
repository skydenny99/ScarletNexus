// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "GA_DodgeBase.generated.h"

class ABaseCharacter;
class UCharacterMovementComponent;
enum class EBaseDirectionType : uint8;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_DodgeBase : public UGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
	TArray<UAnimMontage*> DodgeMontages;

	UPROPERTY()
	UCharacterMovementComponent* DodgeMovementComponent;

	UPROPERTY()
	ABaseCharacter* DodgeCharacter;
	
public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	UFUNCTION(BlueprintCallable, Category = "Dodge")
	void AlignCharacterWithCameraDirection();

	UFUNCTION(BlueprintPure, Category = "Dodge")
	void GetCurrentCharacterLookDirection(const EBaseDirectionType& DirectionResult);
};
