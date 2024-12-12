// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ComboSystemComponent.h"
#include "Character/Character_Kasane.h"

// Sets default values for this component's properties
UComboSystemComponent::UComboSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	Kasane->MovementModeChangedDelegate.AddDynamic(this, &UComboSystemComponent::ResetAllCombo);
}

void UComboSystemComponent::ActivateAbilityByTag(FGameplayTag tag)
{
}

void UComboSystemComponent::UpdateInfoByUnlock()
{
	
}

void UComboSystemComponent::ResetAllCombo(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	ResetAttackCombo();
	ResetBackstepCount();
}

void UComboSystemComponent::ResetAttackCombo()
{
	CurrentGroundComboCount = 0;
	CurrentAerialComboCount = 0;
}

void UComboSystemComponent::ResetBackstepCount()
{
	CurrentBackstepAttackCount = 0;
}

