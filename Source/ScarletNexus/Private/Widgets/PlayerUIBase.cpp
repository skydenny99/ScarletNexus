// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PlayerUIBase.h"

#include "BaseDebugHelper.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/Image.h"
#include "Components/UI/PlayerUIComponent.h"

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

void UPlayerUIBase::SetHpPercent(const float SetPercent)
{
	if (SetPercent >= HpPercent)
	{
		HpBottomProgress = FMath::Clamp( SetPercent - HpPrevTopProgress,0.0f ,1.0f);
		HpMaterialInstance->SetVectorParameterValue("BottomColor",FColor::Green);
	}
	else
	{
		HpBottomProgress += HpPrevTopProgress - SetPercent;
		HpMaterialInstance->SetVectorParameterValue("BottomColor",FColor::Red);
	}
	
	HpPercent = SetPercent;
	bIsActive = true;
}

void UPlayerUIBase::SetPsychkinesis(const float SetPercent)
{
	if (SetPercent >= PsychPercent)
	{
		PsychBottomProgress -= SetPercent - PsychPrevTopProgress;
	}
	else
	{
		PsychBottomProgress += PsychPrevTopProgress - SetPercent;
	}
	
	PsychPercent = SetPercent;
	bIsActive = true;
}

void UPlayerUIBase::UpdateHp(const float TopProgress, const float DeltaSec)
{
	if (HpPrevTopProgress < TopProgress)
	{
		HpMaterialInstance->SetScalarParameterValue("TopProgress", HpPrevTopProgress);
		HpMaterialInstance->SetScalarParameterValue("BottomProgress", HpBottomProgress);

		HpPrevTopProgress = FMath::Min(HpPrevTopProgress + DeltaSec * AnimSpeed, 1.0f);
		HpBottomProgress = FMath::Max(HpBottomProgress - DeltaSec * AnimSpeed, 0.0f);
		if (HpPrevTopProgress == TopProgress)
		{
			bIsActive = false;
		}
	}
	else
	{
		HpPrevTopProgress = TopProgress;
		
		HpMaterialInstance->SetScalarParameterValue("TopProgress", TopProgress);
		HpMaterialInstance->SetScalarParameterValue("BottomProgress", HpBottomProgress);

		HpBottomProgress = FMath::Clamp(HpBottomProgress - DeltaSec * AnimSpeed, 0.0f, HpBottomProgress);
		if (HpBottomProgress == 0.0f)
		{
			bIsActive = false;
		}
	}
}

void UPlayerUIBase::UpdatePsych(const float TopProgress, const float DeltaSec)
{
	PsychPrevTopProgress = TopProgress;
	
	PsychMaterialInstance->SetScalarParameterValue("TopProgress", TopProgress);
	PsychMaterialInstance->SetScalarParameterValue("BottomProgress", PsychBottomProgress);

	PsychBottomProgress = FMath::Max(PsychBottomProgress - DeltaSec * AnimSpeed, 0.0f);
	if (PsychBottomProgress == 0.0f)
	{
		bIsActive = false;
	}
}

void UPlayerUIBase::OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const
{
	Super::OnOwningPlayerUIComponentInitialized(PlayerUIComponent);

	PlayerUIComponent->OnCurrentHpChanged.AddDynamic(this,&UPlayerUIBase::SetHpPercent);
	PlayerUIComponent->OnPsychPercentChanged.AddDynamic(this,&UPlayerUIBase::SetPsychkinesis);
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
