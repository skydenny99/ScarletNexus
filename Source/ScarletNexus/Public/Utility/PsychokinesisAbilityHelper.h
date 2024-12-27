// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class APsychokineticPropBase;
class UComboSystemComponent;
class ACharacter_Kasane;
class UTargetTrackingSpringArmComponent;
class UPsychokinesisComponent;
/**
 * 
 */
struct FPsychokinesisAbilityHelper
{
	static bool HasPsychokineticPropInRange(const ACharacter_Kasane* Kasane);
	static void OnActivatePsychAbility(const ACharacter_Kasane* Kasane);
	static void OnChargingCancelPsychAbility(const ACharacter_Kasane* Kasane);

	static void ActivateThrowPsychAbility(const ACharacter_Kasane* Kasane);
	static void ActivateSpecialPsychAbility();
};
