// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ComboSystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BaseDebugHelper.h"
#include "Character/Character_Kasane.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "DataAsset/DataAsset_AttackAbility.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UComboSystemComponent::UComboSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UComboSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	if (Kasane)
	{
		Kasane->MovementModeChangedDelegate.AddDynamic(this, &UComboSystemComponent::OnMovementModeChange);
	}
}


void UComboSystemComponent::InitKasane(ACharacter_Kasane* InKasane)
{
	Kasane = InKasane;
	if (Kasane)
	{
		BaseAbilitySystemComponent = Kasane->GetBaseAbilitySystemComponent();
	}
}

void UComboSystemComponent::GrantAttackAbilites(UAbilitySystemComponent* ASC, int32 Level)
{
	check(AbilityAsset);
	for (auto AbilityClass : AbilityAsset->AttackAbilityList)
	{
		if (AbilityClass == nullptr) continue;
		FGameplayAbilitySpec Spec(AbilityClass);
		Spec.SourceObject = ASC->GetAvatarActor();
		Spec.Level = Level;
		ASC->GiveAbility(Spec);
		AbilitySpecs.Add(Spec.Ability->AbilityTags.First(), Spec);
	}
	UBaseFunctionLibrary::AddPlaygameTagToActor(Kasane, BaseGameplayTags::Shared_Status_CanAttack);
}

bool UComboSystemComponent::TryActivateAbilityByInputTag(FGameplayTag tag)
{
	FGameplayTag AbilityTag = FGameplayTag();
	UCharacterMovementComponent* Movement = Kasane->GetCharacterMovement();
	if (tag.MatchesTagExact(BaseGameplayTags::InputTag_Attack_Weapon_Normal))
	{
		if (UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Player_Status_ComboDashAttack))
		{
			AbilityTag = Movement->IsFalling() ? BaseGameplayTags::Player_Ability_Attack_Aerial_ComboDashAttack
			: BaseGameplayTags::Player_Ability_Attack_Ground_ComboDashAttack;
		}
		else
		{
			bool bIsDashAttack = UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Player_Status_Move_Dodge);
			if (Movement->IsFalling() == false) // Ground Weapon Attack
			{
				AbilityTag = bIsDashAttack ? BaseGameplayTags::Player_Ability_Attack_Ground_DashAttack
				: BaseGameplayTags::Player_Ability_Attack_Ground_Weapon;
			}
			else
			{
				AbilityTag = bIsDashAttack ? BaseGameplayTags::Player_Ability_Attack_Aerial_DashAttack
				: BaseGameplayTags::Player_Ability_Attack_Aerial_Weapon;
			}
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
		Debug::Print("Triggered: Ability not found", FColor::Red);
		return false;
	}
	if (BaseAbilitySystemComponent->TryActivateAbility(AbilitySpecs[AbilityTag].Handle))
	{
		LastActivatedGameplayTag = AbilityTag;
		return true;
	}
	
	Debug::Print("Triggered: Ability try failed", FColor::Red);
	return false;
}

void UComboSystemComponent::TryActivateChargeAbility()
{
	FGameplayEventData EventData;
	EventData.Instigator = Kasane;
	EventData.InstigatorTags.AddTag(ActionElapsedTime >= ChargeCompletionTime ? BaseGameplayTags::Shared_Event_Charge_Confirm : BaseGameplayTags::Shared_Event_Charge_Cancel);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Kasane, BaseGameplayTags::Shared_Event_Charge, EventData);

	bIsCharging = false;
	UBaseFunctionLibrary::RemovePlayGameTagFromActor(Kasane, BaseGameplayTags::Player_Status_Charging);
	bChargeAbilityAlreadyTriggered = true;
	ActionElapsedTime = 0.f;
}

bool UComboSystemComponent::TryCancelAttackAbility()
{
	if (LastActivatedGameplayTag.IsValid() == false || bIsCharging) return false;
	Debug::Print(FString::Printf(TEXT("Cancel Ability : %s"), *LastActivatedGameplayTag.ToString()), FColor::Red);
	BaseAbilitySystemComponent->CancelAbilityHandle(AbilitySpecs[LastActivatedGameplayTag].Handle);
	LastActivatedGameplayTag = FGameplayTag();
	return true;
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

void UComboSystemComponent::OnMovementModeChange(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	// Reset All Combo;
	Debug::Print("Reset Weapon Combo Count");
	ResetGroundCombo();
	ResetAerialCombo();
	StopPsychComboTimer();
}


void UComboSystemComponent::ProcessInputAction(FGameplayTag InputTag, ETriggerEvent TriggerEvent, const FInputActionInstance& Instance)
{
	switch (TriggerEvent)
	{
	case ETriggerEvent::Triggered:
		if (bIsCharging)
		{
			if (UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Player_Status_Charging))
			{
				ActionElapsedTime = Instance.GetElapsedTime() - StartActionElapsedTime;
				//Debug::Print(FString::Printf(TEXT("Charging %f %f %f"),StartActionElapsedTime, ActionElapsedTime, ChargeCompletionTime), FColor::Blue);
			}
			else
			{
				ActionElapsedTime = 0.f;
				StartActionElapsedTime = Instance.GetElapsedTime();
			}
			if (bIsAutoCompletion && ActionElapsedTime > ChargeCompletionTime)
			{
				TryActivateChargeAbility();
				LastChargeAbilityInputTag = InputTag;
			}
		}
		else
		{
			if (LastChargeAbilityInputTag.MatchesTagExact(InputTag)) return;
			if (TryActivateAbilityByInputTag(InputTag))
			{
				LastChargeAbilityInputTag = InputTag;
			}
		}
		break;
	case ETriggerEvent::Completed:
		if (LastChargeAbilityInputTag.IsValid())
		{
			if (LastChargeAbilityInputTag.MatchesTagExact(InputTag))
			{
				LastChargeAbilityInputTag = FGameplayTag();
			}
			else
			{
				return;
			}
		}
		if (bIsCharging)
		{
				TryActivateChargeAbility();
		}
		else
		{
			if (InputTag == BaseGameplayTags::InputTag_Attack_Weapon_Special)
			{
				// TODO activate or cancel charging ability
				FGameplayTag AbilityTag =
					Kasane->GetCharacterMovement()->IsFalling() ?
						BaseGameplayTags::Player_Ability_Attack_Aerial_Backstep : BaseGameplayTags::Player_Ability_Attack_Ground_Backstep;
				if (AbilityTag.IsValid() == false || AbilitySpecs.Contains(AbilityTag) == false)
				{
					Debug::Print("Completed: Ability not found", FColor::Red);
					return;
				}
				if (BaseAbilitySystemComponent->TryActivateAbility(AbilitySpecs[AbilityTag].Handle))
				{
					LastActivatedGameplayTag = AbilityTag;
					Debug::Print(FString::Printf(TEXT("Ability %s"), *LastActivatedGameplayTag.ToString()), FColor::Red);
				}
				else
				{
					Debug::Print("Completed: Ability try failed", FColor::Red);
				}
			}
		}
			
		break;
	default:
		break;
	}
}


void UComboSystemComponent::IncreaseCombo(FComboCounter& ComboCounter)
{
	ComboCounter.CurrentComboCount = (ComboCounter.CurrentComboCount + 1) % ComboCounter.MaxComboCount;
}

void UComboSystemComponent::ResetGroundCombo()
{
	WeaponGroundCombo.CurrentComboCount = 0;
	PsychGroundCombo.CurrentComboCount = 0;
	BackstepGroundCombo.CurrentComboCount = 0;
}

void UComboSystemComponent::ResetAerialCombo()
{
	WeaponAerialCombo.CurrentComboCount = 0;
	PsychAerialCombo.CurrentComboCount = 0;
	BackstepAerialCombo.CurrentComboCount = 0;
}

void UComboSystemComponent::ResetWeaponCombo()
{
	WeaponGroundCombo.CurrentComboCount = 0;
	WeaponAerialCombo.CurrentComboCount = 0;
}

void UComboSystemComponent::ResetBackstep()
{
	BackstepGroundCombo.CurrentComboCount = 0;
	BackstepAerialCombo.CurrentComboCount = 0;
}

void UComboSystemComponent::StartPsychComboTimer()
{
	bIsPsychComboAttacking = true;
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([this]()
	{
		if (this)
		{
			PsychGroundCombo.CurrentComboCount = 0;
			bIsPsychComboAttacking = false;
			Debug::Print("ResetPsychCombo");
		}
	});
	GetWorld()->GetTimerManager().SetTimer(PsychComboResetTimerHandle, timerDelegate, PsychComboResetTime, false);
}

void UComboSystemComponent::ClearPsychComboTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(PsychComboResetTimerHandle);
}

void UComboSystemComponent::StopPsychComboTimer()
{
	PsychGroundCombo.CurrentComboCount = 0;
	PsychAerialCombo.CurrentComboCount = 0;
	bIsPsychComboAttacking = false;
	ClearPsychComboTimer();
}

void UComboSystemComponent::StartComboDashAttackTimer()
{
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([this]()
	{
		if (this)
		{
			if (Kasane)
			{
				UBaseFunctionLibrary::RemovePlayGameTagFromActor(Kasane, BaseGameplayTags::Player_Status_ComboDashAttack);
			}
		}
	});
	UBaseFunctionLibrary::AddPlaygameTagToActor(Kasane, BaseGameplayTags::Player_Status_ComboDashAttack);
	GetWorld()->GetTimerManager().SetTimer(ComboDashAttackTimerHandle, timerDelegate, ComboDashResetTime, false);
}

