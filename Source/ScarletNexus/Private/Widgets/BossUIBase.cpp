// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BossUIBase.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"
#include "PaperSpriteBlueprintLibrary.h"
//#include "CoreMinimal.h"
//#include "SlateGlobals.h"
//#include "UObject/ObjectMacros.h"
//#include "Application/SlateApplicationBase.h"
//#include "PaperSprite.h"
//#include "Brushes/SlateNoResource.h"
//#include "Kismet/BlueprintFunctionLibrary.h"

/*
#include "SlateGlobals.h"
#include "Application/SlateApplicationBase.h"
#include "Types/SlateVector2.h"*/

void UBossUIBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	HpMaterialDynamicInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), HpMaterial);
	Boss_HealthGauge->SetBrushFromMaterial(HpMaterialDynamicInstance);
	HpMaterialDynamicInstance->SetScalarParameterValue("Percent",1.0f);

	StunMaterialDynamicInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), StunMaterial);
	Boss_StunGauge->SetBrushFromMaterial(StunMaterialDynamicInstance);
	StunMaterialDynamicInstance->SetScalarParameterValue("Percent",1.0f);
	
	Boss_Debuff_Icon->SetVisibility(ESlateVisibility::Collapsed);

	MaxHp = 1000.0f;
	CurrentHp = MaxHp;

	for ( int i = 0; i < DebuffMaterial.Num(); i++)
	{
		//DebuffImage[i]->SetBrush(UPaperSpriteBlueprintLibrary::MakeBrushFromSprite(DebuffMaterial[i],33,33));
	}
}

void UBossUIBase::OnDamaged(float Damage)
{
	CurrentHp -= Damage;

	if (CurrentHp <= 0)
	{
		RemoveFromParent();
	}
	UpdateHp(CurrentHp / MaxHp);
}

void UBossUIBase::UpdateHp(float Value)
{
	HpMaterialDynamicInstance->SetScalarParameterValue("Percent",Value);
}

void UBossUIBase::UpdateStunGauge(float Value)
{
	StunMaterialDynamicInstance->SetScalarParameterValue("Percent",Value);
}

//Input Enum Value
/*
void UBossUIBase::UpdateDebuff(EDebuffState Debuff = EDebuffState::NONE)
{
	if (Debuff == EDebuffState::NONE)
	{
		Boss_Debuff_Icon->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	
	switch (Debuff)
	{
		case EDebuffState::BURN:
			Boss_Debuff_Icon = DebuffImage[0];
			break;
		case EDebuffState::OIL:
			Boss_Debuff_Icon = DebuffImage[1];
			break;
		case EDebuffState::SHOCK:
			Boss_Debuff_Icon = DebuffImage[2];
			break;
		case EDebuffState::WET:
			Boss_Debuff_Icon = DebuffImage[3];
			break;
		case EDebuffState::CONFUSE:
			Boss_Debuff_Icon = DebuffImage[4];
			break;
		default:
			break;
	}
	
	Boss_Debuff_Icon->SetVisibility(ESlateVisibility::Visible);
}
*/

