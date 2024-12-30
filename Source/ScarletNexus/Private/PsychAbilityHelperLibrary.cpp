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

bool UPsychAbilityHelperLibrary::NativeHasPsychokineticPropInRange(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return false;
	const UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	return PsychokinesisComponent ? PsychokinesisComponent->GetPsychTarget() != nullptr : false;
}

void UPsychAbilityHelperLibrary::NativeOnActivatePsychAbility(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	UComboSystemComponent* ComboSystem = Kasane->GetComboSystemComponent();
	if (PsychokinesisComponent && ComboSystem)
	{
		PsychokinesisComponent->SetBlockUpdate(true);
		ComboSystem->SetupChargeProperty(PsychokinesisComponent->GetPsychTarget()->GetChargeTime(), true);
		ComboSystem->StartCharging();
		ComboSystem->ResetWeaponCombo();
	}
}

void UPsychAbilityHelperLibrary::NativeOnChargingCancelPsychAbility(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	if (UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent())
	{
		APsychokineticThrowableProp* ThrowableProp = Cast<APsychokineticThrowableProp>(PsychokinesisComponent->GetPsychTarget());
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
		const auto ThrowableProp = Cast<APsychokineticThrowableProp>(PsychokinesisComponent->GetPsychTarget());

		AActor* TargetActor = TargetTracking->GetCurrentTarget();
		ThrowableProp->SetTarget(TargetActor);
		if(ABaseEnemyCharacter* EnemyCharacter = Cast<ABaseEnemyCharacter>(TargetActor))
		{
			ThrowableProp->SetTarget(EnemyCharacter->GetTargetVector());
		}
		ThrowableProp->Launch(
			UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Player_Status_SAS_Clone),
			true
			);
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
		if (PsychokinesisComponent->GetPsychTarget() == nullptr) return nullptr;
		UGameplayEffect* CostGameplayEffect = NewObject<UGameplayEffect>(GetTransientPackage(), FName("PsychCost"));
		CostGameplayEffect->DurationPolicy = EGameplayEffectDurationType::Instant;

		int32 Idx = CostGameplayEffect->Modifiers.Num();
		CostGameplayEffect->Modifiers.SetNum(Idx + 1);

		FGameplayModifierInfo& InfoCost = CostGameplayEffect->Modifiers[Idx];
		InfoCost.ModifierMagnitude = FScalableFloat(-PsychokinesisComponent->GetPsychTarget()->GetPsychCost());
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
