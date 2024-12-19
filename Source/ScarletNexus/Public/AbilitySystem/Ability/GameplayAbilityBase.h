// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"

enum class EBaseSuccessType : uint8;
class UBaseAbilitySystemComponent;
class UPawnCombatComponent;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGameplayAbilityBase : public UGameplayAbility 
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Ability")
	UBaseAbilitySystemComponent* GetBaseAbilitySystemComponent() const;

	template<class UserObject>
	UserObject* GetOwnerWithCasting() const;

	//CombatComponent 확보
	UFUNCTION(BlueprintPure, Category = "Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Ability", meta=(Display="Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle, EBaseSuccessType& OutSuccessType);
	
};

template<class UserObject>
inline UserObject* UGameplayAbilityBase::GetOwnerWithCasting() const
{
	return Cast<UserObject>(GetOwningActorFromActorInfo());
}
