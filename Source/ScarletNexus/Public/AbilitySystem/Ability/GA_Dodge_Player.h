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
	UPROPERTY(VisibleDefaultsOnly)
	UKasaneAnimInstance* KasaneAnimInstance;

public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void GetCharacterDodgeDirection(EBaseDirectionType& DirectionResult) override;

	UFUNCTION(BlueprintCallable)
	void PlayDodgeAnimation(EBaseDirectionType Direction);
	
	UFUNCTION(BlueprintCallable)
	void OnEndDodge();
};
