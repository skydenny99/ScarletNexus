// Fill out your copyright notice in the Description page of Project Settings.


#include "PsychAbilityHelperLibrary.h"

#include "BaseGameplayTags.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "BaseFunctionLibrary.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "Actor/PsychokineticPropBase.h"
#include "Actor/PsychokineticSpecialPropBase.h"
#include "Actor/PsychokineticThrowableProp.h"
#include "Character/Character_Kasane.h"
#include "Character/EnemyCharacter/BaseEnemyCharacter.h"
#include "Components/ComboSystemComponent.h"
#include "Components/PsychokinesisComponent.h"
#include "Components/TargetTrackingSpringArmComponent.h"

void UPsychAbilityHelperLibrary::NativeOnActivatePsychAbilityInternal(const ACharacter_Kasane* Kasane,
	APsychokineticPropBase* Prop)
{
	if (Kasane == nullptr) return;
	UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	UComboSystemComponent* ComboSystem = Kasane->GetComboSystemComponent();
	if (PsychokinesisComponent && ComboSystem)
	{
		PsychokinesisComponent->SetCurrentPsychTarget(Prop);
		PsychokinesisComponent->SetBlockUpdate(true);
		ComboSystem->OnUpdateChargeGauge.BindUObject(Prop, &APsychokineticPropBase::OnUpdatePsychChargeGauge);
		ComboSystem->SetupChargeProperty(PsychokinesisComponent->GetCurrentPsychTarget()->GetChargeTime(), true);
		ComboSystem->StartCharging();
		ComboSystem->ResetWeaponCombo();
	}
}

void UPsychAbilityHelperLibrary::NativeOverrideThrowablePsychObject(const ACharacter_Kasane* Kasane, AActor* PsychObject)
{
	if (Kasane == nullptr) return;
	if (UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent())
	{
		PsychokinesisComponent->SetBlockUpdate(true);
		PsychokinesisComponent->OverrideThrowableTarget(PsychObject);
		PsychokinesisComponent->SetCurrentPsychTarget(PsychokinesisComponent->GetPsychThrowableTarget());
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
	if (UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent())
	{
		NativeOnActivatePsychAbilityInternal(Kasane, PsychokinesisComponent->GetPsychThrowableTarget());
	}
}

void UPsychAbilityHelperLibrary::NativeOnActivateSpecialPsychAbility(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	if (UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent())
	{
		NativeOnActivatePsychAbilityInternal(Kasane, PsychokinesisComponent->GetPsychSpecialTarget());
	}
}

void UPsychAbilityHelperLibrary::CancelChargingPsychAbility(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	UComboSystemComponent* ComboSystem = Kasane->GetComboSystemComponent();
	if (PsychokinesisComponent && ComboSystem)
	{
		APsychokineticThrowableProp* ThrowableProp = Cast<APsychokineticThrowableProp>(PsychokinesisComponent->GetCurrentPsychTarget());
		if (ThrowableProp)
		{
			ThrowableProp->OnChargingCancel();
			ComboSystem->OnUpdateChargeGauge.Unbind();
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

void UPsychAbilityHelperLibrary::SetPropDamageHandle(UGameplayAbility* Ability, ACharacter_Kasane* Kasane, float Level,
	TSubclassOf<UGameplayEffect> DamageEffectClass)
{
	if (Kasane == nullptr || DamageEffectClass == nullptr) return;

	if (UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent())
	{
		APsychokineticThrowableProp* ThrowableProp = Cast<APsychokineticThrowableProp>(PsychokinesisComponent->GetPsychThrowableTarget());
		if (ThrowableProp)
		{
			
			FGameplayEffectContextHandle ContextHandle;
			ContextHandle.SetAbility(Ability);
			ContextHandle.AddSourceObject(Kasane);
			ContextHandle.AddInstigator(Kasane, Kasane);

			FGameplayEffectSpecHandle SpecHandle = Kasane->GetBaseAbilitySystemComponent()->MakeOutgoingSpec(
				DamageEffectClass,
				Level,
				ContextHandle
			);
	
			SpecHandle.Data->SetSetByCallerMagnitude(BaseGameplayTags::Shared_SetByCaller_BaseDamage,ThrowableProp->GetDamage());
			ThrowableProp->SetDamageHandle(SpecHandle);
		}
	}
}

void UPsychAbilityHelperLibrary::ActivateSpecialPsychAbility(ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	if (UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent())
	{
		if (APsychokineticSpecialPropBase* SpecialProp = Cast<APsychokineticSpecialPropBase>(PsychokinesisComponent->GetPsychSpecialTarget()))
		{
			if (auto ASC = Kasane->GetBaseAbilitySystemComponent())
			{
				FGameplayAbilitySpec AbilitySpec(SpecialProp->GetSpecialPsychAbilityClass());
				AbilitySpec.SourceObject = Kasane;
				AbilitySpec.Level = 1;
				ASC->GiveAbility(AbilitySpec);
			}
		}
	}
}

void UPsychAbilityHelperLibrary::SetBlockUpdateTarget(const ACharacter_Kasane* Kasane, bool InBlock)
{
	if (Kasane == nullptr) return;
	if (UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent())
	{
		//Debug::Print(FString::Printf(TEXT("%s"), *FString(InBlock ? "BlockUpdateTarget true" : "BlockUpdateTarget false")));
		PsychokinesisComponent->SetBlockUpdate(InBlock);
	}
}

UGameplayEffect* UPsychAbilityHelperLibrary::CreatePsychCostGameplayEffect(const ACharacter_Kasane* Kasane, APsychokineticPropBase* Target)
{
	if (Kasane == nullptr || Target == nullptr) return nullptr;
	UGameplayEffect* CostGameplayEffect = NewObject<UGameplayEffect>(GetTransientPackage(), FName("PsychCost"));
	CostGameplayEffect->DurationPolicy = EGameplayEffectDurationType::Instant;

	int32 Idx = CostGameplayEffect->Modifiers.Num();
	CostGameplayEffect->Modifiers.SetNum(Idx + 1);

	FGameplayModifierInfo& InfoCost = CostGameplayEffect->Modifiers[Idx];
	InfoCost.ModifierMagnitude = FScalableFloat(-Target->GetPsychCost());
	InfoCost.ModifierOp = EGameplayModOp::Additive;
	InfoCost.Attribute = UPlayerAttributeSet::GetCurrentPsychGaugeAttribute();
	return CostGameplayEffect;
}

void UPsychAbilityHelperLibrary::ApplyPsychCostGameplayEffect(const ACharacter_Kasane* Kasane)
{
	if (const UGameplayEffect* CostGameplayEffect = CreatePsychCostGameplayEffect(Kasane, Kasane->GetPsychokinesisComponent()->GetCurrentPsychTarget()))
	{
		auto ASC = Kasane->GetBaseAbilitySystemComponent();
		ASC->ApplyGameplayEffectToSelf(CostGameplayEffect, 1.f, ASC->MakeEffectContext());
	}
}

void UPsychAbilityHelperLibrary::ApplyPsychRecoverGameplayEffect(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	FGameplayTag LastAttackType = Kasane->GetComboSystemComponent()->GetAttackType();
	if (LastAttackType.IsValid() == false) return;
	
	UGameplayEffect* CostGameplayEffect = NewObject<UGameplayEffect>(GetTransientPackage(), FName("PsychRecover"));
	CostGameplayEffect->DurationPolicy = EGameplayEffectDurationType::Instant;

	int32 Idx = CostGameplayEffect->Modifiers.Num();
	CostGameplayEffect->Modifiers.SetNum(Idx + 1);

	FGameplayModifierInfo& InfoCost = CostGameplayEffect->Modifiers[Idx];
	int32 RecoverAmount = (LastAttackType == BaseGameplayTags::Player_Ability_Attack_Aerial_Backstep
		|| LastAttackType == BaseGameplayTags::Player_Ability_Attack_Ground_Backstep) ? 50 : 10;
	InfoCost.ModifierMagnitude = FScalableFloat(RecoverAmount);
	InfoCost.ModifierOp = EGameplayModOp::Additive;
	InfoCost.Attribute = UPlayerAttributeSet::GetCurrentPsychGaugeAttribute();
	auto ASC = Kasane->GetBaseAbilitySystemComponent();
	ASC->ApplyGameplayEffectToSelf(CostGameplayEffect, 1.f, ASC->MakeEffectContext());
}

void UPsychAbilityHelperLibrary::InitOnGrabThrowableProp(ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	UTargetTrackingSpringArmComponent* TargetTracking = Kasane->GetTargetTrackingComponent();
	UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	if (auto ThrowableProp = Cast<APsychokineticThrowableProp>(PsychokinesisComponent->GetPsychThrowableTarget()))
	{
		ThrowableProp->OnStartGrab(
		UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Player_Status_SAS_Clone),
		true);
		AActor* TargetActor = TargetTracking->GetCurrentTarget();
		ThrowableProp->SetTarget(TargetActor);
		if(ABaseEnemyCharacter* EnemyCharacter = Cast<ABaseEnemyCharacter>(TargetActor))
		{
			ThrowableProp->SetTarget(EnemyCharacter->GetTargetVector());
		}
	}
}


