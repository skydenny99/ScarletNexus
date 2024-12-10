// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GA_DodgeBase.h"
#include "GA_Dodge_Player.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_Dodge_Player : public UGA_DodgeBase
{
	GENERATED_BODY()
protected:
	FORCEINLINE bool CheckDirection(uint8 Lhs, EBaseDirectionType RHS) const;

public:
	virtual void GetCharacterDodgeDirection(EBaseDirectionType& DirectionResult) override;
};
