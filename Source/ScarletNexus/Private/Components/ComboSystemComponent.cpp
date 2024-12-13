// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ComboSystemComponent.h"

#include "BaseDebugHelper.h"
#include "Character/Character_Kasane.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"

// Sets default values for this component's properties
UComboSystemComponent::UComboSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	Kasane = Cast<ACharacter_Kasane>(GetOwner());
	if (Kasane)
	{
		Kasane->MovementModeChangedDelegate.AddDynamic(this, &UComboSystemComponent::ResetAllCombo);
	}
}


void UComboSystemComponent::ActivateAbilityByTag(FGameplayTag tag)
{
	//if (tag.MatchesTagExact(BaseGameplayTags::playerability))
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

void UComboSystemComponent::ProcessInputAction(FGameplayTag ActionTag, ETriggerEvent TriggerEvent, const FInputActionInstance& Instance)
{
	switch (TriggerEvent)
	{
	case ETriggerEvent::Triggered:
		if (ActionTag == LastActivatedGameplayTag)
			ActionElapsedTime = Instance.GetElapsedTime();
		if (ShouldBlockInputAction()) return;
		ActivateAbilityByTag(ActionTag);
		break;
	case ETriggerEvent::Completed:
		// TODO activate charging ability
		break;
	default:
		break;
	}
}

bool UComboSystemComponent::ShouldBlockInputAction()
{
	if (UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Player_Status_Charging))
		return true;
	
	return false;
}


