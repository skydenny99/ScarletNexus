// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ItemUIBase.h"

#include "ToolContextInterfaces.h"
#include "Components/Image.h"
#include "Basetype/BaseStructType.h"
#include "Kismet/KismetMaterialLibrary.h"

void UItemUIBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ArrowMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),ArrowMaterial);
	DownArrow_B->SetBrushFromMaterial(ArrowMaterialInstance);
}

void UItemUIBase::UpdateGauge(const FConsumItemInfo& Item)
{
	ItemMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Item.Material);
	Item_Progressbar->SetBrushFromMaterial(ItemMaterialInstance);
	ItemMaterialInstance->SetVectorParameterValue("Color",Item.Color);
	ItemMaterialInstance->SetScalarParameterValue("Percent",Item.Percentage);

	ArrowMaterialInstance->SetVectorParameterValue("Color",Item.Color);

	if (Item.Percentage >= 1)
	{
		//blink
	}
}

