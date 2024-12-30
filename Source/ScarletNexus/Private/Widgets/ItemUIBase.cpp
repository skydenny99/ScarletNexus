// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ItemUIBase.h"
#include "Components/Image.h"
#include "Basetype/BaseStructType.h"
#include "Components/UI/PlayerUIComponent.h"
#include "Kismet/KismetMaterialLibrary.h"

void UItemUIBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ArrowMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),ArrowMaterial);
	DownArrow_B->SetBrushFromMaterial(ArrowMaterialInstance);
	GaugeMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),GaugeMaterial);
	Item_Progressbar->SetBrushFromMaterial(GaugeMaterialInstance);
	GaugeMaterialInstance->SetScalarParameterValue("Progress", 1.0f);
}

void UItemUIBase::UpdateGauge(const FColor& Color, float Percent)
{
	GaugeMaterialInstance->SetVectorParameterValue("Color",Color);
	GaugeMaterialInstance->SetScalarParameterValue("Percent",Percent);
	
	ArrowMaterialInstance->SetVectorParameterValue("Color",Color);
}

void UItemUIBase::OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const
{
	Super::OnOwningPlayerUIComponentInitialized(PlayerUIComponent);

	//PlayerUIComponent->OnCurrentItemChanged.AddDynamic(this,&UItemUIBase::UpdateGauge);
}
