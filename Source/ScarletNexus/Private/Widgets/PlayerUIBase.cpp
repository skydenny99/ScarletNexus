// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlayerUIBase.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/Image.h"

void UPlayerUIBase::NativeConstruct()
{
	Super::NativeConstruct();

	HpMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),HpMaterial);
	PlayerHp->SetBrushFromMaterial(HpMaterialInstance);
	HpMaterialInstance->SetScalarParameterValue("TopProgress", 1.0f);
	
	PsychMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),PsychMaterial);
	PsychGauge->SetBrushFromMaterial(PsychMaterialInstance);
	PsychMaterialInstance->SetScalarParameterValue("TopProgress",1.0f);

	AnimSpeed = 0.15f;
	HpPercent = 1.0f;
	HpPrevTopProgress = 1.0f;
	HpBottomProgress = 0.0f;
	PsychPercent = 1.0f;
	PsychPrevTopProgress = 1.0f;
	PsychBottomProgress = 0.0f;
	bIsActive = false;
}

void UPlayerUIBase::OnDamaged(const float SetPercent)
{
	HpPercent = SetPercent;
	bIsActive = true;
}

void UPlayerUIBase::SetPsychkinesis(const float SetPercent)
{
	PsychPercent = SetPercent;
	bIsActive = true;
}

void UPlayerUIBase::UpdateHp(const float TopProgress, const float DeltaSec)
{
	HpBottomProgress += HpPrevTopProgress - TopProgress ;
	HpPrevTopProgress = TopProgress;

	HpMaterialInstance->SetScalarParameterValue("TopProgress", TopProgress);
	HpMaterialInstance->SetScalarParameterValue("BottomProgress", HpBottomProgress);

	HpBottomProgress = FMath::Clamp(HpBottomProgress - DeltaSec * AnimSpeed, 0.0f, HpBottomProgress);
	if (HpBottomProgress == 0.0f)
	{
		bIsActive = false;
	}
}

void UPlayerUIBase::UpdatePsych(const float TopProgress, const float DeltaSec)
{
	PsychBottomProgress +=  PsychPrevTopProgress - TopProgress;
	PsychPrevTopProgress = TopProgress;

	PsychMaterialInstance->SetScalarParameterValue("TopProgress", TopProgress);
	PsychMaterialInstance->SetScalarParameterValue("BottomProgress", PsychBottomProgress);

	PsychBottomProgress = FMath::Clamp(PsychBottomProgress - DeltaSec * AnimSpeed, 0.0f, PsychBottomProgress);
	if (HpBottomProgress == 0.0f)
	{
		bIsActive = false;
	}
}

void UPlayerUIBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsActive == false && HpBottomProgress == 0.0f && PsychBottomProgress == 0.0f)
	{
		return;
	}
	UpdateHp(HpPercent,InDeltaTime);
	UpdatePsych(PsychPercent,InDeltaTime);
}
