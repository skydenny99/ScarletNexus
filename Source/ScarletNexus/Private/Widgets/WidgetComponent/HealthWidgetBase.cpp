// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WidgetComponent/HealthWidgetBase.h"

#include "AssetRegistry/IAssetRegistry.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/Image.h"


void UHealthWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	HpMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),HpMaterial);
	HealthGauge->SetBrushFromMaterial(HpMaterialInstance);
	HpMaterialInstance->SetScalarParameterValue("TopProgress",1.0f);

	BrainCrashMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),BrainCrashMaterial);
	StunGauge->SetBrushFromMaterial(BrainCrashMaterialInstance);
	BrainCrashMaterialInstance->SetScalarParameterValue("Percent",1.0f);

	PrevTopProgress = 1.0f;
	BottomProgress = 0.0f;
	AnimSpeed = 0.15f;
	Percent = 1.0;
	bIsActive = false;
}

void UHealthWidgetBase::SetHealthGauge(const float SetPercent)
{
	Percent = SetPercent;
	bIsActive = true;
}

void UHealthWidgetBase::UpdateBrainCrashGauge(const float SetPercent)
{
	BrainCrashMaterialInstance->SetScalarParameterValue("Percent",SetPercent);
}

void UHealthWidgetBase::UpdateHealthGauge(const float TopProgress, const float DeltaSec)
{
	BottomProgress += PrevTopProgress - TopProgress;
	PrevTopProgress = TopProgress;

	HpMaterialInstance->SetScalarParameterValue("TopProgress", TopProgress);
	HpMaterialInstance->SetScalarParameterValue("BottomProgress", BottomProgress);

	BottomProgress = FMath::Clamp(BottomProgress - DeltaSec * AnimSpeed, 0.0f, BottomProgress);
	if (BottomProgress == 0.0f)
	{
		bIsActive = false;
	}
}

void UHealthWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsActive == false && BottomProgress == 0.0f)
	{
		return;
	}
	
	UpdateHealthGauge(Percent, InDeltaTime);
}
