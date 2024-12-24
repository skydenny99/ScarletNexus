// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BossUIBase.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"

void UBossUIBase::NativeConstruct()
{
	Super::NativeConstruct();

	HpDynamicMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), HpMaterial);
	Boss_HealthGauge->SetBrushFromMaterial(HpDynamicMaterialInstance);
	HpDynamicMaterialInstance->SetScalarParameterValue("TopProgress",1.0f);
	
	StunDynamicMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), StunMaterial);
	Boss_StunGauge->SetBrushFromMaterial(StunDynamicMaterialInstance);
	StunDynamicMaterialInstance->SetScalarParameterValue("Percent",1.0f);
	
	Boss_Debuff_Icon->SetVisibility(ESlateVisibility::Hidden);

	Percent = 1.0f;
	PrevTopProgress = 1.0f;
	BottomProgress = 0.0f;
	AnimationSpeed = 0.15f;
	bIsActive = false;
}

void UBossUIBase::OnDamaged(const float SetPercent)
{
	Percent = SetPercent;
	UE_LOG(LogTemp, Warning, TEXT("percent : %f"),Percent);
	bIsActive = true;
}

void UBossUIBase::UpdateHp(const float TopProgress, const float DeltaSec)
{
	BottomProgress += PrevTopProgress - TopProgress;
	PrevTopProgress = TopProgress;

	HpDynamicMaterialInstance->SetScalarParameterValue("TopProgress",TopProgress);
	HpDynamicMaterialInstance->SetScalarParameterValue("BottomProgress",BottomProgress);
	const float Value = BottomProgress - DeltaSec * AnimationSpeed;
	BottomProgress = FMath::Clamp(Value,0.0f,BottomProgress);
	if (BottomProgress == 0.0f)
	{
		bIsActive = false;
	}
}

inline void UBossUIBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsActive == false && BottomProgress == 0.0f)
	{
		return;
	}
	UpdateHp(Percent, InDeltaTime);
}

void UBossUIBase::UpdateStunGauge(const float Value)
{
	StunDynamicMaterialInstance->SetScalarParameterValue("Percent",Value);
}

