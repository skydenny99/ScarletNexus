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

void UItemUIBase::UpdateGauge(const FConsumItemInfo Item)
{
	GaugeMaterialInstance->SetVectorParameterValue("Color",Item.Color);
	GaugeMaterialInstance->SetScalarParameterValue("Percent",Item.Percentage);

	ArrowMaterialInstance->SetVectorParameterValue("Color",Item.Color);

	if (Item.Percentage >= 1)
	{
		//blink
	}
}

void UItemUIBase::OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const
{
	Super::OnOwningPlayerUIComponentInitialized(PlayerUIComponent);

	PlayerUIComponent->OnCurrentItemChanged.AddDynamic(this,&UItemUIBase::UpdateGauge);
}
