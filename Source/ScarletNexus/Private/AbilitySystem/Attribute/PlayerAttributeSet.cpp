// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attribute/PlayerAttributeSet.h"

#include <string>

#include "GameplayEffectExtension.h"
#include "BaseDebugHelper.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/PlayerUIComponent.h"
#include "Interfaces/PawnUIInterface.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	InitCurrentHp(1.f);
	InitMaxHp(1.f);
	InitPower(1.f);
	InitAttack(1.f);
	InitDefence(1.f);
	InitDamageTaken(1.f);
	InitCurrentPsychGauge(1.f);
	InitMaxPsychGauge(1.f);
	
	InitCurrentFireGauge(1.f);
	InitMaxFireGauge(1.f);
	InitCurrentAccelGauge(1.f);
	InitMaxAccelGauge(1.f);
	InitCurrentCloneGauge(1.f);
	InitMaxCloneGauge(1.f);
	InitCurrentStealthGauge(1.f);
	InitMaxStealthGauge(1.f);
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (!CachedUIInterface.IsValid())
	{
		CachedUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedUIInterface.IsValid(), TEXT("%s does not Implemetation IPawnUIInterface."), *Data.Target.GetAvatarActor()->GetActorLabel());
	UPawnUIComponent* PawnUIComponent = CachedUIInterface->GetPawnUIComponent();
	checkf(PawnUIComponent, TEXT("Can not Load PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorLabel());

	UPlayerUIComponent* PlayerUIComponent = CachedUIInterface->GetPlayerUIComponent();
	
	
	if (Data.EvaluatedData.Attribute == GetCurrentHpAttribute())
	{
		const float NewCurrentHp = FMath::Clamp(GetCurrentHp(), 0.0f, GetMaxHp());
		SetCurrentHp(NewCurrentHp);
		PawnUIComponent->OnCurrentHpValueChanged.Broadcast(NewCurrentHp);
		//Debug::Print(FString::Printf(TEXT("HP = %f"),NewCurrentHp));
		
	}
	

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float BeforeHp = GetCurrentHp();
		
		const float Damage = GetDamageTaken();
		
		const float CashedDefence = GetDefence();
		
		// HP
		const float NewCurrentHp = FMath::Clamp(BeforeHp - (Damage - CashedDefence), 0.0f, GetMaxHp());
		SetCurrentHp(NewCurrentHp);
		
		

		const FString DebugString = FString::Printf(TEXT("Before Hp: %f, Damage: %f, NewCurrentHp : %f"), BeforeHp, Damage, NewCurrentHp);
		//Debug::Print(DebugString, FColor::Green);
	}

	if (Data.EvaluatedData.Attribute == GetCurrentPsychGaugeAttribute())
	{
		const float NewCurrentFireGauge = FMath::Clamp(GetCurrentPsychGauge(), 0.0f, GetMaxPsychGauge());
		SetCurrentPsychGauge(NewCurrentFireGauge);
	}


	if (Data.EvaluatedData.Attribute == GetCurrentFireGaugeAttribute())
	{
		const float NewCurrentFireGauge = FMath::Clamp(GetCurrentFireGauge(), 0.0f, GetMaxFireGauge());
		SetCurrentFireGauge(NewCurrentFireGauge);
	}

	if (Data.EvaluatedData.Attribute == GetCurrentAccelGaugeAttribute())
	{
		const float NewCurrentAccelGauge = FMath::Clamp(GetCurrentAccelGauge(), 0.0f, GetMaxAccelGauge());
		SetCurrentAccelGauge(NewCurrentAccelGauge);
	}
	
	if (Data.EvaluatedData.Attribute == GetCurrentCloneGaugeAttribute())
	{
		const float NewCurrentCloneGauge = FMath::Clamp(GetCurrentCloneGauge(), 0.0f, GetMaxCloneGauge());
		SetCurrentCloneGauge(NewCurrentCloneGauge);
	}
	
	if (Data.EvaluatedData.Attribute == GetCurrentStealthGaugeAttribute())
	{
		const float NewCurrentStealthGauge = FMath::Clamp(GetCurrentStealthGauge(), 0.0f, GetMaxStealthGauge());
		SetCurrentStealthGauge(NewCurrentStealthGauge);
	}
	
	
	if (Data.EvaluatedData.Attribute == GetMaxFireGaugeAttribute())
	{
		SetMaxFireGauge(GetMaxFireGauge());
		SetCurrentFireGauge(GetMaxFireGauge());
	}

	if (Data.EvaluatedData.Attribute == GetMaxAccelGaugeAttribute())
	{
		SetMaxAccelGauge(GetMaxAccelGauge());
		SetCurrentAccelGauge(GetMaxAccelGauge());
	}
	
	if (Data.EvaluatedData.Attribute == GetMaxCloneGaugeAttribute())
	{
		SetMaxCloneGauge(GetMaxCloneGauge());
		SetCurrentCloneGauge(GetMaxCloneGauge());
	}
	
	if (Data.EvaluatedData.Attribute == GetMaxStealthGaugeAttribute())
	{
		SetMaxStealthGauge(GetMaxStealthGauge());
		SetCurrentStealthGauge(GetMaxStealthGauge());
	}
}
