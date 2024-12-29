// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "BaseFunctionLibrary.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent(): ItemDataTable(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

FUsableItemInfo UInventoryComponent::GetItemInfo(const FName& ItemName) const
{
	return *ItemDataTable->FindRow<FUsableItemInfo>(ItemName, "");
}


bool UInventoryComponent::HasItem(const FName& ItemName, FInventoryItemInfo& FoundItemInfo) const
{
	for (auto ItemInfo : Inventory)
	{
		if (ItemInfo.ItemName == ItemName && ItemInfo.CurrentCount > 0)
		{
			FoundItemInfo = ItemInfo;
			return true;
		}
	}
	return false;
}

void UInventoryComponent::ChangeIndex(bool InIsLeft)
{
	CurrentIndex = (CurrentIndex + (InIsLeft ? -1 : 1) + Inventory.Num()) % Inventory.Num();
}

void UInventoryComponent::UseCurrentSelectedItem(AActor* Target)
{
	UseItemByName(Target, Inventory[CurrentIndex].ItemName);
}

void UInventoryComponent::UseItemByName(AActor* Target, const FName& ItemName)
{
	FInventoryItemInfo FoundItem;
	if (HasItem(ItemName, FoundItem) == false) return;
	auto ASC = UBaseFunctionLibrary::NativeGetAbilitySystemComponentFromActor(Target);
	if (ASC)
	{
		FoundItem.CurrentCount--;
		FUsableItemInfo* ItemInfo = ItemDataTable->FindRow<FUsableItemInfo>(ItemName, "");
		ASC->ApplyGameplayEffectToSelf(ItemInfo->ItemGameplayEffectClass.GetDefaultObject(), 1.f, ASC->MakeEffectContext());
	}
}
