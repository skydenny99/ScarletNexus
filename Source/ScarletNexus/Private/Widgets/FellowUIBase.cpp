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
	LeftHpPercent = 1.0f;
	LPrevTopProgress = 1.0f;
	LBottomProgress = 0.0f;
	RightHpPercent = 1.0f;
	RPrevTopProgress = 1.0f;
	RBottomProgress = 0.0f;
	bIsActive = false;
}

void UFellowUIBase::OnDamagedRFellow(const float SetPercent)
{
	RightHpPercent = SetPercent;
	bIsActive = true;
}

void UFellowUIBase::OnDamagedLFellow(const float SetPercent)
{
	LeftHpPercent = SetPercent;
	bIsActive = true;
}

void UFellowUIBase::UpdateRightHp(const float TopProgress, const float DeltaSec)
{
	RBottomProgress += RPrevTopProgress - TopProgress;
	RPrevTopProgress = TopProgress;

	RightMaterialInstance->SetScalarParameterValue("TopProgress", TopProgress);
	RightMaterialInstance->SetScalarParameterValue("BottomProgress", RBottomProgress);

	RBottomProgress = FMath::Clamp(RBottomProgress - DeltaSec * AnimSpeed, 0.0f, RBottomProgress);
	if (RBottomProgress == 0.0f)
	{
		bIsActive = false;
	}
}

void UFellowUIBase::UpdateLeftHp(const float TopProgress, const float DeltaSec)
{
	LBottomProgress += LPrevTopProgress - TopProgress;
	LPrevTopProgress = TopProgress;

	LeftMaterialInstance->SetScalarParameterValue("TopProgress", TopProgress);
	LeftMaterialInstance->SetScalarParameterValue("BottomProgress", LBottomProgress);

	LBottomProgress = FMath::Clamp(LBottomProgress - DeltaSec * AnimSpeed, 0.0f, LBottomProgress);
	if (LBottomProgress == 0.0f)
	{
		bIsActive = false;
	}
}

void UFellowUIBase::OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const
{
	Super::OnOwningPlayerUIComponentInitialized(PlayerUIComponent);

	PlayerUIComponent->OnUpdateFellowLeftHpPercent.AddDynamic(this,&UFellowUIBase::OnDamagedLFellow);
	PlayerUIComponent->OnUpdateFellowRightHpPercent.AddDynamic(this,&UFellowUIBase::OnDamagedRFellow);
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


