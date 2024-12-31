// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GA_SpecialPsych.h"
#include "Actor/PsychokineticPropBase.h"
#include "PsychokineticSpecialPropBase.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API APsychokineticSpecialPropBase : public APsychokineticPropBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGA_SpecialPsych> SpecialPsychAbilityClass;

public:
	FORCEINLINE TSubclassOf<UGA_SpecialPsych> GetSpecialPsychAbilityClass() const {return SpecialPsychAbilityClass;};
};
