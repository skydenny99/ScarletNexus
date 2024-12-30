// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "GA_UseItemBase.generated.h"

class ACharacter_Kasane;
class UInventoryComponent;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_UseItemBase : public UGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	ACharacter_Kasane *Kasane;
	
	UPROPERTY()
	UInventoryComponent* InventoryComponent;
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	UFUNCTION(BlueprintCallable)
	void UseCurrentSelectedItem();
};
