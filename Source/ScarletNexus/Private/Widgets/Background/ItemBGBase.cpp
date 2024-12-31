// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Background/ItemBGBase.h"
#include "BaseType/BaseStructType.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Styling/SlateBrush.h"
#include "PaperSpriteBlueprintLibrary.h"
#include "Character/Character_Kasane.h"
#include "Components/InventoryComponent.h"
#include "Components/UI/PlayerUIComponent.h"

void UItemBGBase::NativeConstruct()
{
	Super::NativeConstruct();

	GlowMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),GlowMaterial);
	Glow->SetBrushFromMaterial(GlowMaterialInstance);
	Glow->SetColorAndOpacity(FColor::Green);
	Glow->SetOpacity(0.1f);

	
	//UE_LOG(LogTemp,Warning,TEXT("OwningPlayer : %s"),*GetOwningPlayer()->GetName());
	check(GetOwningPlayer());
	
	check(Cast<ACharacter_Kasane>(GetOwningPlayer()->GetPawn())->GetInventoryComponent());
	
	InventoryComponent = Cast<ACharacter_Kasane>(GetOwningPlayer()->GetPawn())->GetInventoryComponent();

	Init(0);
}

int UItemBGBase::Side(const int Index,const int Lenght, const bool bIsLeft)
{
	return bIsLeft ? (Index-1 + Lenght) % Lenght : (Index+1 + Lenght) % Lenght;
}

void UItemBGBase::UpdateBefore(int32 OldIndex ,bool bIsLeft)
{
	TArray<FInventoryItemInfo> Items = InventoryComponent->GetInventoryItems();
	const int Index = Side(OldIndex,Items.Num(),bIsLeft);
	CachedCurrentIndex = Index;

	Glow->SetColorAndOpacity(InventoryComponent->GetItemInfo(Items[Index].ItemName).Color);
	T_ItemName->SetText(FText::FromName(InventoryComponent->GetItemInfo(Items[Index].ItemName).ItemDisplayName));
	Glow->SetOpacity(0.1f);

	if (bIsLeft)
	{
		LeftSwapMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),InventoryComponent->GetItemInfo(Items[Side(Index,Items.Num(),bIsLeft)].ItemName).ItemMaterial);
		Item_Right_Swap->SetBrushFromMaterial(MiddleMaterialInstance);
		Item_Middle_Swap->SetBrushFromMaterial(LeftMaterialInstance);
		Item_Left_Swap->SetBrushFromMaterial(LeftSwapMaterialInstance);

		LeftQuantity->SetText(FText::FromString(FString::FromInt(Items[Side(Index,Items.Num(),true)].CurrentCount)));
		MiddleQuantity->SetText(FText::FromString(FString::FromInt(Items[Index].CurrentCount)));
		//RightQuantity->SetText(FText::FromString(FString::FromInt(Items[Side(OldIndex,Items.Num(),false)].CurrentCount)));
		RightQuantity->SetText(FText::FromString(FString::FromInt(Items[OldIndex].CurrentCount)));
	}
	else
	{
		RightSwapMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),InventoryComponent->GetItemInfo(Items[Side(Index,Items.Num(),bIsLeft)].ItemName).ItemMaterial);
		Item_Left_Swap->SetBrushFromMaterial(MiddleMaterialInstance);
		Item_Middle_Swap->SetBrushFromMaterial(RightMaterialInstance);
		Item_Right_Swap->SetBrushFromMaterial(RightSwapMaterialInstance);
		
		LeftQuantity->SetText(FText::FromString(FString::FromInt(Items[OldIndex].CurrentCount)));
		MiddleQuantity->SetText(FText::FromString(FString::FromInt(Items[Index].CurrentCount)));
		RightQuantity->SetText(FText::FromString(FString::FromInt(Items[Side(Index,Items.Num(),false)].CurrentCount)));
	}
}

void UItemBGBase::UpdateAfter(int32 CurrentIndex)
{
	TArray<FInventoryItemInfo> Items = InventoryComponent->GetInventoryItems();

	LeftMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),InventoryComponent->GetItemInfo(Items[Side(CurrentIndex,Items.Num(),true)].ItemName).ItemMaterial);
	MiddleMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),InventoryComponent->GetItemInfo(Items[CurrentIndex].ItemName).ItemMaterial);
	RightMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),InventoryComponent->GetItemInfo(Items[Side(CurrentIndex,Items.Num(),false)].ItemName).ItemMaterial);
	Item_Left->SetBrushFromMaterial(LeftMaterialInstance);
	Item_Middle->SetBrushFromMaterial(MiddleMaterialInstance);
	Item_Right->SetBrushFromMaterial(RightMaterialInstance);
	Glow->SetOpacity(0.1f);
}

void UItemBGBase::Init(int32 CurrentIndex)
{
	TArray<FInventoryItemInfo> Items = InventoryComponent->GetInventoryItems();
	const int LIndex = Side(CurrentIndex,Items.Num(),true);
	const int RIndex = Side(CurrentIndex,Items.Num(),false);

	LeftSwapMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),InventoryComponent->GetItemInfo(Items[Side(LIndex,Items.Num(),true)].ItemName).ItemMaterial);
	LeftMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),InventoryComponent->GetItemInfo(Items[LIndex].ItemName).ItemMaterial);
	MiddleMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),InventoryComponent->GetItemInfo(Items[CurrentIndex].ItemName).ItemMaterial);
	MiddleSwapMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),InventoryComponent->GetItemInfo(Items[CurrentIndex].ItemName).ItemMaterial);
	RightMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),InventoryComponent->GetItemInfo(Items[Side(CurrentIndex,Items.Num(),false)].ItemName).ItemMaterial);
	RightSwapMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),InventoryComponent->GetItemInfo(Items[Side(RIndex,Items.Num(),false)].ItemName).ItemMaterial);
	Item_Left->SetBrushFromMaterial(LeftSwapMaterialInstance);
	Item_Middle->SetBrushFromMaterial(MiddleSwapMaterialInstance);
	Item_Right->SetBrushFromMaterial(RightSwapMaterialInstance);
	
	Glow->SetColorAndOpacity(InventoryComponent->GetItemInfo(Items[CurrentIndex].ItemName).Color);
	T_ItemName->SetText(FText::FromName(InventoryComponent->GetItemInfo(Items[CurrentIndex].ItemName).ItemDisplayName));
	Glow->SetOpacity(0.1f);

	LeftQuantity->SetText(FText::FromString(FString::FromInt(Items[LIndex].CurrentCount)));
	MiddleQuantity->SetText(FText::FromString(FString::FromInt(Items[CurrentIndex].CurrentCount)));
	RightQuantity->SetText(FText::FromString(FString::FromInt(Items[RIndex].CurrentCount)));
}

void UItemBGBase::UpdateQuantity(int32 CurrentIndex)
{
	
	TArray<FInventoryItemInfo> Items = InventoryComponent->GetInventoryItems();
	const int LIndex = Side(CurrentIndex,Items.Num(),true);
	const int RIndex = Side(CurrentIndex,Items.Num(),false);
	
	LeftQuantity->SetText(FText::FromString(FString::FromInt(Items[LIndex].CurrentCount)));
	MiddleQuantity->SetText(FText::FromString(FString::FromInt(Items[CurrentIndex].CurrentCount)));
	RightQuantity->SetText(FText::FromString(FString::FromInt(Items[RIndex].CurrentCount)));
}

void UItemBGBase::SetGlowVisibility(float Percent)
{
	if (Percent < 1)
	{
		Glow->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}
	if (Percent == 1.0f)
	{
		Glow->SetVisibility(ESlateVisibility::Visible);
	}
}

void UItemBGBase::OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const
{
	Super::OnOwningPlayerUIComponentInitialized(PlayerUIComponent);

	//PlayerUIComponent->OnItemInit.AddDynamic(this,&UItemBGBase::Init);
	//PlayerUIComponent->OnUpdateAfter.AddDynamic(this,&UItemBGBase::UpdateAfter);
	//PlayerUIComponent->OnUpdateBefore.AddDynamic(this,&UItemBGBase::UpdateBefore);
}
