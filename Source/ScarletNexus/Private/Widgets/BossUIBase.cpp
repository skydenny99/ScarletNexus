// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BossUIBase.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/Image.h"
#include "PaperSprite.h"
#include "Math/UnrealMathNeon.h"
#include "Styling/SlateBrush.h"

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
void UBossUIBase::UpdateDebuff(int Enum)
{
	
	/*
	switch (Enum)
	{
	case 0:
		
		A.SetResourceObject(DebuffMaterial[0]);
		Boss_Debuff_Icon->SetBrush(A);
		break;
	case 1:
		//FSlateBrush B();
		A.SetResourceObject(DebuffMaterial[1]);
		Boss_Debuff_Icon->SetBrush(A);
		break;
	case 2:
		//FSlateBrush C();
		A.SetResourceObject(DebuffMaterial[2]);
		Boss_Debuff_Icon->SetBrush(A);
		break;
	case 3:
		//FSlateBrush D();
		A.SetResourceObject(DebuffMaterial[3]);
		Boss_Debuff_Icon->SetBrush(A);
		break;
	case 4:
		//FSlateBrush E();
		A.SetResourceObject(DebuffMaterial[4]);
		Boss_Debuff_Icon->SetBrush(A);
		break;
	default:
		break;
	}*/
}

