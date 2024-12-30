// Fill out your copyright notice in the Description page of Project Settings.


#include "PsychAbilityHelperLibrary.h"

#include "BaseGameplayTags.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
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
	UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	if (PsychokinesisComponent)
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
	UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	if (PsychokinesisComponent)
	{
		APsychokineticThrowableProp* ThrowableProp = Cast<APsychokineticThrowableProp>(PsychokinesisComponent->GetPsychTarget());
		if (ThrowableProp)
		{
			ThrowableProp->OnChargingCancel();
		}
	}
}

void UPsychAbilityHelperLibrary::ActivateThrowPsychAbility(const ACharacter_Kasane* Kasane)
{
	if (Kasane == nullptr) return;
	UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	UTargetTrackingSpringArmComponent* TargetTracking = Kasane->GetTargetTrackingComponent();
	if (PsychokinesisComponent && TargetTracking)
	{
		const auto ThrowableProp = Cast<APsychokineticThrowableProp>(PsychokinesisComponent->GetPsychTarget());

		AActor* TargetActor = TargetTracking->GetCurrentTarget();
		ABaseEnemyCharacter* EnemyCharacter = Cast<ABaseEnemyCharacter>(TargetActor);

		if(TargetActor && EnemyCharacter)
		{
			ThrowableProp->SetTarget(EnemyCharacter->GetTargetVector());
			ThrowableProp->Launch();
		}
		else
		{
			ThrowableProp->Launch();
		}
	}
}

void UPsychAbilityHelperLibrary::SetPropDamageHandle(UGameplayAbility* Ability, ACharacter_Kasane* Kasane, float Level,
	TSubclassOf<UGameplayEffect> DamageEffectClass)
{
	if (Kasane == nullptr || DamageEffectClass == nullptr) return;

	if (UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent())
	{
		APsychokineticThrowableProp* ThrowableProp = Cast<APsychokineticThrowableProp>(PsychokinesisComponent->GetPsychTarget());
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

void UPsychAbilityHelperLibrary::ActivateSpecialPsychAbility()
{
}

void UPsychAbilityHelperLibrary::SetBlockUpdateTarget(const ACharacter_Kasane* Kasane, bool InBlock)
{
	if (Kasane == nullptr) return;
	UPsychokinesisComponent* PsychokinesisComponent = Kasane->GetPsychokinesisComponent();
	if (PsychokinesisComponent)
	{
		PsychokinesisComponent->SetBlockUpdate(InBlock);
	}
}
