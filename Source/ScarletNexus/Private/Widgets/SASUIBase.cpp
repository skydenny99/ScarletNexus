// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SASUIBase.h"

#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Widgets/BossUIBase.h"
#include "Components/UI/PlayerUIComponent.h"

void USASUIBase::InitTopGauge(const FColor Color, const float Percent)
{
	UE_LOG(LogTemp, Display, TEXT("USASUIBase::InitTopGauge"));
	SAS_T_Dynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), SAS_Gauge);
	T_Gauge->SetBrushFromMaterial(SAS_T_Dynamic);
	SAS_T_Dynamic->SetScalarParameterValue("Percent",Percent);
	SAS_T_Dynamic->SetVectorParameterValue("Color",Color);
}

void USASUIBase::InitLeftGauge(const FColor Color, const float Percent)
{
	UE_LOG(LogTemp, Display, TEXT("USASUIBase::InitLeftGauge"));
	SAS_L_Dynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), SAS_Gauge);
	L_Gauge->SetBrushFromMaterial(SAS_L_Dynamic);
	SAS_L_Dynamic->SetScalarParameterValue("Percent",Percent);
	SAS_L_Dynamic->SetVectorParameterValue("Color",Color);
}

void USASUIBase::InitRightGauge(const FColor Color, const float Percent)
{
	UE_LOG(LogTemp, Display, TEXT("USASUIBase::InitRightGauge"));
	SAS_R_Dynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), SAS_Gauge);
	R_Gauge->SetBrushFromMaterial(SAS_R_Dynamic);
	SAS_R_Dynamic->SetScalarParameterValue("Percent",Percent);
	SAS_R_Dynamic->SetVectorParameterValue("Color",Color);
}

void USASUIBase::InitBottomGauge(const FColor Color, const float Percent)
{
	UE_LOG(LogTemp, Display, TEXT("USASUIBase::InitBottomGauge"));
	SAS_B_Dynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), SAS_Gauge);
	B_Gauge->SetBrushFromMaterial(SAS_B_Dynamic);
	SAS_B_Dynamic->SetScalarParameterValue("Percent",Percent);
	SAS_B_Dynamic->SetVectorParameterValue("Color",Color);
}

void USASUIBase::UpdateTopGauge(const float Percent)
{
	SAS_T_Dynamic->SetScalarParameterValue("Percent",Percent);
}

void USASUIBase::UpdateLeftGauge(const float Percent)
{
	SAS_L_Dynamic->SetScalarParameterValue("Percent",Percent);
}

void USASUIBase::UpdateRightGauge(const float Percent)
{
	SAS_R_Dynamic->SetScalarParameterValue("Percent",Percent);
}

void USASUIBase::UpdateBottomGauge(const float Percent)
{
	SAS_B_Dynamic->SetScalarParameterValue("Percent",Percent);
}

void USASUIBase::OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const
{
	Super::OnOwningPlayerUIComponentInitialized(PlayerUIComponent);

	PlayerUIComponent->OnInitSASSimbol.AddDynamic(this,&USASUIBase::InitSprite);
	PlayerUIComponent->OnInitTopGauge.AddDynamic(this,&USASUIBase::InitTopGauge);
	PlayerUIComponent->OnInitLeftGauge.AddDynamic(this,&USASUIBase::InitLeftGauge);
	PlayerUIComponent->OnInitRightGauge.AddDynamic(this,&USASUIBase::InitRightGauge);
	PlayerUIComponent->OnInitBottomGauge.AddDynamic(this,&USASUIBase::InitBottomGauge);
	PlayerUIComponent->OnUpdateSASTopGauge.AddDynamic(this,&USASUIBase::UpdateTopGauge);
	PlayerUIComponent->OnUpdateSASLeftGauge.AddDynamic(this,&USASUIBase::UpdateLeftGauge);
	PlayerUIComponent->OnUpdateSASRightGauge.AddDynamic(this,&USASUIBase::UpdateRightGauge);
	PlayerUIComponent->OnUpdateSASBottomGauge.AddDynamic(this,&USASUIBase::UpdateBottomGauge);
}


