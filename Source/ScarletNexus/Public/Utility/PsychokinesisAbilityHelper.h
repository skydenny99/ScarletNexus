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
class SCARLETNEXUS_API PsychokinesisAbilityHelper
{
protected:
	UPsychokinesisComponent* PsychokinesisComponent = nullptr;
	UTargetTrackingSpringArmComponent* TargetTrackingComponent = nullptr;
	UComboSystemComponent* ComboSystemComponent = nullptr;
	APsychokineticPropBase* CurrentPsychTarget = nullptr;

	void InitComponents(ACharacter_Kasane* Character);
	bool HasPsychokineticPropInRange() const;
	void OnActivatePsychAbility();

	void ActivateThrowPsychAbility();
	void ActivateSpecialPsychAbility();
};
