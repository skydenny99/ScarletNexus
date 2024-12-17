// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbilityBase.generated.h"

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
	
};

template<class UserObject>
inline UserObject* UGameplayAbilityBase::GetOwnerWithCasting() const
{
	return Cast<UserObject>(GetOwningActorFromActorInfo());
}
