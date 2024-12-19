// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ItemUIBase.h"

#include "Components/Image.h"
#include "Kismet/KismetMaterialLibrary.h"


void UItemUIBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	ProgressbarInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Progressbar);
	Item_Progressbar->SetBrushFromMaterial(ProgressbarInstance);
	ProgressbarInstance->SetScalarParameterValue("Percent",1.0f);
}

void UItemUIBase::OnUseItem()
{
	
}
