// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BossUIBase.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"
#include "PaperSpriteBlueprintLibrary.h"
#include "BaseType/BaseEnumType.h"

void UBossUIBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	HpMaterialDynamicInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), HpMaterial);
	Boss_HealthGauge->SetBrushFromMaterial(HpMaterialDynamicInstance);
	HpMaterialDynamicInstance->SetScalarParameterValue("Percent",1.0f);

	StunMaterialDynamicInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), StunMaterial);
	Boss_StunGauge->SetBrushFromMaterial(StunMaterialDynamicInstance);
	StunMaterialDynamicInstance->SetScalarParameterValue("Percent",1.0f);
	
	Boss_Debuff_Icon->SetVisibility(ESlateVisibility::Hidden);

	MaxHp = 1000.0f;
	CurrentHp = MaxHp;
}

void UBossUIBase::OnDamaged(const float Damage)
{
	CurrentHp -= Damage;

	if (CurrentHp <= 0)
	{
		RemoveFromParent();
	}
	
	UpdateHp(CurrentHp / MaxHp);

	UpdateDebuff(EBaseDebuffType::CONFUSE);
}

void UBossUIBase::UpdateHp(const float Value)
{
	HpMaterialDynamicInstance->SetScalarParameterValue("Percent",Value);
}

void UBossUIBase::UpdateStunGauge(const float Value)
{
	StunMaterialDynamicInstance->SetScalarParameterValue("Percent",Value);
}
