// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Background/ItemBGBase.h"
#include "BaseType/BaseStructType.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMaterialLibrary.h"

void UItemBGBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UE_LOG(LogTemp, Warning, TEXT("UItemBGBase::NativeOnInitialize"));
	GlowMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),GlowMaterial);
	Glow->SetBrushFromMaterial(GlowMaterialInstance);
	auto c = FFloat16(0x25EE341A);
	Glow->SetColorAndOpacity(FColor::Green);
	Glow->SetOpacity(0.1f);
}

void UItemBGBase::UpdateBGItemBeforeSwap(const TArray<FConsumItemInfo>& Items, const int32 Front, const bool bIsRight)
{
	const int32 Rear = (Items.Num()-1+Front)%Items.Num();
	
	if (bIsRight)
	{
		T_ItemName->SetText(FText::FromName(Items[Front+1].Name));
		LeftMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Items[Rear].Material);
		LeftSwapMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Items[Rear-1].Material);
		MiddleMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Items[Front].Material);
		MiddleSwapMaterialInstance = LeftMaterialInstance;
		RightMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Items[Front+1].Material);
		RightSwapMaterialInstance = MiddleMaterialInstance;
		Glow->SetColorAndOpacity(Items[Front+1].Color);
	}
	else
	{
		T_ItemName->SetText(FText::FromName(Items[Rear].Name));
		RightMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Items[Front+1].Material);
		RightSwapMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Items[Front+2].Material);
		MiddleMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Items[Front].Material);
		MiddleSwapMaterialInstance = RightMaterialInstance;
		LeftMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Items[Rear].Material);
		LeftSwapMaterialInstance = MiddleMaterialInstance;
		Glow->SetColorAndOpacity(Items[Rear].Color);
	}
}

void UItemBGBase::UpdateBGItem(const TArray<FConsumItemInfo>& Items, const int32 Front)
{
	const int32 Rear = (Items.Num()-1+Front)%Items.Num();
	T_ItemName->SetText(FText::FromName(Items[Front].Name));
	LeftMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Items[Rear].Material);
	MiddleMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Items[Front].Material);
	RightMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Items[Front+1].Material);
	Glow->SetColorAndOpacity(Items[Front].Color);
	//Glow->SetOpacity(0.1f);
}
