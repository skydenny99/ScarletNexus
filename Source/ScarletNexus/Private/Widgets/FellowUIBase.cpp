// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/FellowUIBase.h"
#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/UI/PlayerUIComponent.h"

void UFellowUIBase::NativeConstruct()
{
	Super::NativeConstruct();

	RightMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),HpMaterial);
	Right_Hp->SetBrushFromMaterial(RightMaterialInstance);
	RightMaterialInstance->SetScalarParameterValue("TopProgress",1.0f);
	
	LeftMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),HpMaterial);
	Left_Hp->SetBrushFromMaterial(LeftMaterialInstance);
	LeftMaterialInstance->SetScalarParameterValue("TopProgress",1.0f);

	AnimSpeed = 0.15f;
	
	RightHpPercent = 1.0f;
	RPrevTopProgress = 1.0f;
	RBottomProgress = 0.0f;
	
	LeftHpPercent = 1.0f;
	LPrevTopProgress = 1.0f;
	LBottomProgress = 0.0f;
	
	bIsActive = false;
}

void UFellowUIBase::SetPercentRFellow(const float SetPercent)
{
	if (SetPercent >= RightHpPercent)
	{
		RBottomProgress = FMath::Clamp( SetPercent - RPrevTopProgress,0.0f ,1.0f);
		RightMaterialInstance->SetVectorParameterValue("BottomColor",FColor::Green);
	}
	else
	{
		RBottomProgress += RPrevTopProgress - SetPercent;
		RightMaterialInstance->SetVectorParameterValue("BottomColor",FColor::Red);
	}
	
	RightHpPercent = SetPercent;
	bIsActive = true;
}

void UFellowUIBase::SetPercentLFellow(const float SetPercent)
{
	if (SetPercent >= LeftHpPercent)
	{
		LBottomProgress = FMath::Clamp( SetPercent - LPrevTopProgress,0.0f ,1.0f);
		LeftMaterialInstance->SetVectorParameterValue("BottomColor",FColor::Green);
	}
	else
	{
		LBottomProgress += LPrevTopProgress - SetPercent;
		LeftMaterialInstance->SetVectorParameterValue("BottomColor",FColor::Red);
	}
	
	LeftHpPercent = SetPercent;
	bIsActive = true;
}

void UFellowUIBase::UpdateRightHp(const float TopProgress, const float DeltaSec)
{
	if (RPrevTopProgress < TopProgress)
	{
		RightMaterialInstance->SetScalarParameterValue("TopProgress", RPrevTopProgress);
		RightMaterialInstance->SetScalarParameterValue("BottomProgress", RBottomProgress);

		RPrevTopProgress = FMath::Min(RPrevTopProgress + DeltaSec * AnimSpeed, 1.0f);
		RBottomProgress = FMath::Max(RBottomProgress - DeltaSec * AnimSpeed, 0.0f);
		if (RPrevTopProgress == TopProgress)
		{
			bIsActive = false;
		}
	}
	else
	{
		RPrevTopProgress = TopProgress;
		
		RightMaterialInstance->SetScalarParameterValue("TopProgress", TopProgress);
		RightMaterialInstance->SetScalarParameterValue("BottomProgress", RBottomProgress);

		RBottomProgress = FMath::Clamp(RBottomProgress - DeltaSec * AnimSpeed, 0.0f, RBottomProgress);
		if (RBottomProgress == 0.0f)
		{
			bIsActive = false;
		}
	}
}

void UFellowUIBase::UpdateLeftHp(const float TopProgress, const float DeltaSec)
{
	if (LPrevTopProgress < TopProgress)
	{
		LeftMaterialInstance->SetScalarParameterValue("TopProgress", LPrevTopProgress);
		LeftMaterialInstance->SetScalarParameterValue("BottomProgress", LBottomProgress);

		LPrevTopProgress = FMath::Min(LPrevTopProgress + DeltaSec * AnimSpeed, 1.0f);
		LBottomProgress = FMath::Max(LBottomProgress - DeltaSec * AnimSpeed, 0.0f);
		if (LPrevTopProgress == TopProgress)
		{
			bIsActive = false;
		}
	}
	else
	{
		LPrevTopProgress = TopProgress;
		
		LeftMaterialInstance->SetScalarParameterValue("TopProgress", TopProgress);
		LeftMaterialInstance->SetScalarParameterValue("BottomProgress", LBottomProgress);

		LBottomProgress = FMath::Clamp(LBottomProgress - DeltaSec * AnimSpeed, 0.0f, LBottomProgress);
		if (LBottomProgress == 0.0f)
		{
			bIsActive = false;
		}
	}
}

void UFellowUIBase::OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const
{
	Super::OnOwningPlayerUIComponentInitialized(PlayerUIComponent);

	PlayerUIComponent->OnUpdateFellowLeftHpPercent.AddDynamic(this,&UFellowUIBase::SetPercentLFellow);
	PlayerUIComponent->OnUpdateFellowRightHpPercent.AddDynamic(this,&UFellowUIBase::SetPercentRFellow);
}

void UFellowUIBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bIsActive == false && LBottomProgress == 0.0f && RBottomProgress == 0.0f)
	{
		return;
	}
	UpdateRightHp(RightHpPercent, InDeltaTime);
	UpdateLeftHp(LeftHpPercent, InDeltaTime);
}


