// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Background/ItemBGBase.h"
#include "BaseType/BaseStructType.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Styling/SlateBrush.h"
#include "PaperSpriteBlueprintLibrary.h"
#include "Components/UI/PlayerUIComponent.h"

void UItemBGBase::NativeConstruct()
{
	Super::NativeConstruct();

	GlowMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),GlowMaterial);
	Glow->SetBrushFromMaterial(GlowMaterialInstance);
	Glow->SetColorAndOpacity(FColor::Green);
	Glow->SetOpacity(0.1f);
}

int UItemBGBase::Side(const int Index,const int Lenght, const bool bIsLeft)
{
	return bIsLeft ? (Index-1 + Lenght) % Lenght : (Index+1 + Lenght) % Lenght;
}

void UItemBGBase::UpdateBefore(const TArray<FConsumItemInfo>& Items, int32 Middle,bool bIsLeft)
{
	const int Index = Side(Middle,Items.Num(),bIsLeft);

	Glow->SetColorAndOpacity(Items[Index].Color);
	T_ItemName->SetText(FText::FromName(Items[Index].Name));
	Glow->SetOpacity(0.1f);

	if (bIsLeft)
	{
		LeftSwapMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Items[Side(Index,Items.Num(),bIsLeft)].ItemMaterial);
		Item_Right_Swap->SetBrushFromMaterial(MiddleMaterialInstance);
		Item_Middle_Swap->SetBrushFromMaterial(LeftMaterialInstance);
		Item_Left_Swap->SetBrushFromMaterial(LeftSwapMaterialInstance);
	}
	else
	{
		RightSwapMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Items[Side(Index,Items.Num(),bIsLeft)].ItemMaterial);
		Item_Left_Swap->SetBrushFromMaterial(MiddleMaterialInstance);
		Item_Middle_Swap->SetBrushFromMaterial(RightMaterialInstance);
		Item_Right_Swap->SetBrushFromMaterial(RightSwapMaterialInstance);
	}
}

void UItemBGBase::UpdateAfter(const TArray<FConsumItemInfo>& Items, int32 Middle)
{
	LeftMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Items[Side(Middle,Items.Num(),true)].ItemMaterial);
	MiddleMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Items[Middle].ItemMaterial);
	RightMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Items[Side(Middle,Items.Num(),false)].ItemMaterial);
	Item_Left->SetBrushFromMaterial(LeftMaterialInstance);
	Item_Middle->SetBrushFromMaterial(MiddleMaterialInstance);
	Item_Right->SetBrushFromMaterial(RightMaterialInstance);
	Glow->SetOpacity(0.1f);
}

void UItemBGBase::Init(const TArray<FConsumItemInfo>& Items, int32 Middle)
{
	const int Index = Side(Middle,Items.Num(),true);

	LeftSwapMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Items[Side(Index,Items.Num(),true)].ItemMaterial);
	LeftMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Items[Side(Middle,Items.Num(),true)].ItemMaterial);
	MiddleMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Items[Middle].ItemMaterial);
	MiddleSwapMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Items[Middle].ItemMaterial);
	RightMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Items[Side(Middle,Items.Num(),false)].ItemMaterial);
	RightSwapMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Items[Side(Index,Items.Num(),false)].ItemMaterial);
	Item_Left->SetBrushFromMaterial(LeftSwapMaterialInstance);
	Item_Middle->SetBrushFromMaterial(MiddleSwapMaterialInstance);
	Item_Right->SetBrushFromMaterial(RightSwapMaterialInstance);
	
	Glow->SetColorAndOpacity(Items[Middle].Color);
	T_ItemName->SetText(FText::FromName(Items[Middle].Name));
	Glow->SetOpacity(0.1f);
}

void UItemBGBase::OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const
{
	Super::OnOwningPlayerUIComponentInitialized(PlayerUIComponent);

	PlayerUIComponent->OnItemInit.AddDynamic(this,&UItemBGBase::Init);
	PlayerUIComponent->OnUpdateAfter.AddDynamic(this,&UItemBGBase::UpdateAfter);
	PlayerUIComponent->OnUpdateBefore.AddDynamic(this,&UItemBGBase::UpdateBefore);
}
