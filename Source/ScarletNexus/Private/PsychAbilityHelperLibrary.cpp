// Fill out your copyright notice in the Description page of Project Settings.


#include "PsychAbilityHelperLibrary.h"

#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "Actor/PsychokineticPropBase.h"
#include "Actor/PsychokineticThrowableProp.h"
#include "Character/Character_Kasane.h"
#include "Character/EnemyCharacter/BaseEnemyCharacter.h"
#include "Components/ComboSystemComponent.h"
#include "Components/PsychokinesisComponent.h"
#include "Components/TargetTrackingSpringArmComponent.h"

void UPsychAbilityHelperLibrary::NativeSetPsychObject(const ACharacter_Kasane* Kasane, AActor* PsychObject)
{
	if (Kasane == nullptr) return;
	if (UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent())
	{
		PsychokinesisComponent->SetBlockUpdate(true);
		PsychokinesisComponent->SetPsychTargetInForce(PsychObject);
	}
}

bool UPsychAbilityHelperLibrary::NativeHasPsychokineticThrowablePropInRange(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return false;
	const UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	return PsychokinesisComponent ? PsychokinesisComponent->GetPsychThrowableTarget() != nullptr : false;
}

bool UPsychAbilityHelperLibrary::NativeHasPsychokineticSpecialPropInRange(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return false;
	const UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	return PsychokinesisComponent ? PsychokinesisComponent->GetPsychSpecialTarget() != nullptr : false;
}

void UPsychAbilityHelperLibrary::NativeOnActivateNormalPsychAbility(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	UComboSystemComponent* ComboSystem = Kasane->GetComboSystemComponent();
	if (PsychokinesisComponent && ComboSystem)
	{
		PsychokinesisComponent->SetCurrentPsychTarget(PsychokinesisComponent->GetPsychThrowableTarget());
		PsychokinesisComponent->SetBlockUpdate(true);
		ComboSystem->SetupChargeProperty(PsychokinesisComponent->GetCurrentPsychTarget()->GetChargeTime(), true);
		ComboSystem->StartCharging();
		ComboSystem->ResetWeaponCombo();
	}
}

void UPsychAbilityHelperLibrary::NativeOnActivateSpecialPsychAbility(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	UComboSystemComponent* ComboSystem = Kasane->GetComboSystemComponent();
	if (PsychokinesisComponent && ComboSystem)
	{
		PsychokinesisComponent->SetCurrentPsychTarget(PsychokinesisComponent->GetPsychSpecialTarget());
		PsychokinesisComponent->SetBlockUpdate(true);
		ComboSystem->SetupChargeProperty(PsychokinesisComponent->GetCurrentPsychTarget()->GetChargeTime(), true);
		ComboSystem->StartCharging();
		ComboSystem->ResetWeaponCombo();
	}
}

void UPsychAbilityHelperLibrary::NativeOnChargingCancelPsychAbility(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	if (UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent())
	{
		APsychokineticThrowableProp* ThrowableProp = Cast<APsychokineticThrowableProp>(PsychokinesisComponent->GetCurrentPsychTarget());
		if (ThrowableProp)
		{
			ThrowableProp->OnChargingCancel();
		}
	}
}

void UPsychAbilityHelperLibrary::ActivateThrowPsychAbility(ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	UTargetTrackingSpringArmComponent* TargetTracking = Kasane->GetTargetTrackingComponent();
	if (PsychokinesisComponent && TargetTracking)
	{
		const auto ThrowableProp = Cast<APsychokineticThrowableProp>(PsychokinesisComponent->GetCurrentPsychTarget());

		AActor* TargetActor = TargetTracking->GetCurrentTarget();
		ThrowableProp->SetTarget(TargetActor);
		if(ABaseEnemyCharacter* EnemyCharacter = Cast<ABaseEnemyCharacter>(TargetActor))
		{
			ThrowableProp->SetTarget(EnemyCharacter->GetTargetVector());
		}
		ThrowableProp->Launch();
	}
}

void UPsychAbilityHelperLibrary::ActivateSpecialPsychAbility()
{
}

void UPsychAbilityHelperLibrary::SetBlockUpdateTarget(const ACharacter_Kasane* Kasane, bool InBlock)
{
	if (Kasane == nullptr) return;
	if (UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent())
	{
		PsychokinesisComponent->SetBlockUpdate(InBlock);
	}
}

UGameplayEffect* UPsychAbilityHelperLibrary::CreatePsychCostGameplayEffect(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return nullptr;
	if (UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent())
	{
		if (PsychokinesisComponent->GetCurrentPsychTarget() == nullptr) return nullptr;
		UGameplayEffect* CostGameplayEffect = NewObject<UGameplayEffect>(GetTransientPackage(), FName("PsychCost"));
		CostGameplayEffect->DurationPolicy = EGameplayEffectDurationType::Instant;

		int32 Idx = CostGameplayEffect->Modifiers.Num();
		CostGameplayEffect->Modifiers.SetNum(Idx + 1);

		FGameplayModifierInfo& InfoCost = CostGameplayEffect->Modifiers[Idx];
		InfoCost.ModifierMagnitude = FScalableFloat(-PsychokinesisComponent->GetCurrentPsychTarget()->GetPsychCost());
		InfoCost.ModifierOp = EGameplayModOp::Additive;
		InfoCost.Attribute = UPlayerAttributeSet::GetCurrentPsychGaugeAttribute();
		return CostGameplayEffect;
	}
	return nullptr;
}

void UPsychAbilityHelperLibrary::ApplyPsychCostGameplayEffect(const ACharacter_Kasane* Kasane)
{
	UGameplayEffect* CostGameplayEffect = CreatePsychCostGameplayEffect(Kasane);
	if (CostGameplayEffect)
	{
		auto ASC = Kasane->GetBaseAbilitySystemComponent();
		ASC->ApplyGameplayEffectToSelf(CostGameplayEffect, 1.f, ASC->MakeEffectContext());
	}
}
