// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ComboSystemComponent.h"

#include "BaseDebugHelper.h"
#include "Character/Character_Kasane.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
		BaseAbilitySystemComponent = Kasane->GetBaseAbilitySystemComponent();
	}
}


void UComboSystemComponent::GrantAttackAbilites(UAbilitySystemComponent* ASC, int32 Level)
{
	TArray<TSubclassOf<UGameplayAbilityBase>> Abilites;
	Abilites.Add(WeaponGroundAttackAbility);
	Abilites.Add(WeaponAerialAttackAbility);
	Abilites.Add(PsychGroundAttackAbility);
	Abilites.Add(PsychAerialAttackAbility);
	Abilites.Add(WeaponBackstepAbility);
	Abilites.Add(WeaponChargeAttackAbility);
	Abilites.Add(PsychSpecialAttackAbility);
	for (auto AbilityClass : Abilites)
	{
		if (AbilityClass == nullptr) continue;
		FGameplayAbilitySpec Spec(AbilityClass);
		Spec.SourceObject = ASC->GetAvatarActor();
		Spec.Level = Level;
		ASC->GiveAbility(Spec);
		AbilitySpecs.Add(Spec.Ability->AbilityTags.First(), Spec);
	}
}

void UComboSystemComponent::TryActivateAbilityByInputTag(FGameplayTag tag)
{
	FGameplayTag AbilityTag = FGameplayTag();
	UCharacterMovementComponent* Movement = Kasane->GetCharacterMovement();
	if (tag.MatchesTagExact(BaseGameplayTags::InputTag_Attack_Weapon_Normal))
	{
		if (Movement->IsFalling() == false) // Ground Weapon Attack
		{
			AbilityTag = BaseGameplayTags::Player_Ability_Attack_Ground_Weapon;
		}
		else
		{
			AbilityTag = BaseGameplayTags::Player_Ability_Attack_Aerial_Weapon;
		}
	}
	else if (tag.MatchesTagExact(BaseGameplayTags::InputTag_Attack_Weapon_Special))
	{
		if (Movement->IsFalling() == false && ActionElapsedTime > ChargeAttackThreshold)
		{
			AbilityTag = BaseGameplayTags::Player_Ability_Attack_Ground_Charge;
		}
	}
	else if (tag.MatchesTagExact(BaseGameplayTags::InputTag_Attack_Psych_Normal))
	{
		if (Movement->IsFalling() == false) // Ground Psych Attack
		{
			AbilityTag = BaseGameplayTags::Player_Ability_Attack_Ground_Psych;
		}
		else
		{
			AbilityTag = BaseGameplayTags::Player_Ability_Attack_Aerial_Psych;
		}
	}
	else if (tag.MatchesTagExact(BaseGameplayTags::InputTag_Attack_Psych_Special))
	{
		AbilityTag = BaseGameplayTags::Player_Ability_Attack_Special_Psych;
	}
	
	if (AbilityTag.IsValid() == false || AbilitySpecs.Contains(AbilityTag) == false)
	{
		Debug::Print("Ability not found", FColor::Red);
		return;
	}
	if (BaseAbilitySystemComponent->TryActivateAbility(AbilitySpecs[AbilityTag].Handle))
	{
		LastActivatedGameplayTag = AbilityTag;
	}
	else
	{
		Debug::Print("Ability try failed", FColor::Red);
	}
}

void UComboSystemComponent::UpdateInfoByUnlock()
{
	if (UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Unlock_GroundCombo_Third))
	{
		WeaponGroundCombo.MaxComboCount = 3;
	}

	if (UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Unlock_GroundCombo_Fourth))
	{
		WeaponGroundCombo.MaxComboCount = 4;
	}
}

void UComboSystemComponent::ResetAllCombo(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	ResetAttackCombo();
	ResetBackstepCount();
}

void UComboSystemComponent::ResetAttackCombo()
{
	WeaponGroundCombo.CurrentComboCount = 0;
	WeaponAerialCombo.CurrentComboCount = 0;
	PsychGroundCombo.CurrentComboCount = 0;
	PsychAerialCombo.CurrentComboCount = 0;
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
		TryActivateAbilityByInputTag(ActionTag);
		break;
	case ETriggerEvent::Completed:
			if (ActionTag == BaseGameplayTags::InputTag_Attack_Weapon_Special)
			{
				// TODO activate or cancel charging ability
			}
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

void UComboSystemComponent::IncreaseCombo(FComboCounter& ComboCounter)
{
	ComboCounter.CurrentComboCount = (ComboCounter.CurrentComboCount + 1) % ComboCounter.MaxComboCount;
}

