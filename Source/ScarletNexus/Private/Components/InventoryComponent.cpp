// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"

#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"

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

bool UInventoryComponent::CanUseItem()
{
	if (Inventory.IsEmpty()) return false;
	return Inventory[CurrentIndex].CurrentCount > 0;
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
	//Debug::Print(FString::Printf(TEXT("Current Inventory: %d"), Inventory.Num()));
	if (Inventory.IsEmpty()) return;
	int32 LastIndex = CurrentIndex;
	CurrentIndex = (CurrentIndex + (InIsLeft ? -1 : 1) + Inventory.Num()) % Inventory.Num();
	OnChangeSelectedItemDelegate.Broadcast(LastIndex, CurrentIndex, InIsLeft);
	//Debug::Print(FString::Printf(TEXT("Current Item: %s"), *Inventory[CurrentIndex].ItemName.ToString()));
}

FUsableItemInfo UInventoryComponent::GetCurrentSelectedItemInfo() const
{
	return GetItemInfo(Inventory[CurrentIndex].ItemName);
}

void UInventoryComponent::UseCurrentSelectedItem(AActor* Target)
{
	UseItemByName(Target, Inventory[CurrentIndex].ItemName);

	OnUseItemDelegate.Broadcast(CurrentIndex);
}

void UInventoryComponent::UseItemByName(AActor* Target, const FName& ItemName)
{
	FInventoryItemInfo FoundItem;
	if (HasItem(ItemName, FoundItem) == false) return;
	
	auto ASC = UBaseFunctionLibrary::NativeGetAbilitySystemComponentFromActor(Target);
	if (ASC)
	{
		for (auto& ItemInfo : Inventory)
		{
			if (ItemInfo.ItemName == ItemName)
			{
				ItemInfo.CurrentCount--;
				break;
			}
		}
		//FoundItem.CurrentCount--;
		FUsableItemInfo* ItemInfo = ItemDataTable->FindRow<FUsableItemInfo>(ItemName, "");
		ASC->ApplyGameplayEffectToSelf(ItemInfo->GE_ItemEffect.GetDefaultObject(), ItemInfo->Level, ASC->MakeEffectContext());
		ASC->ApplyGameplayEffectToSelf(ItemInfo->GE_ItemCooldown.GetDefaultObject(), ItemInfo->Level, ASC->MakeEffectContext());
	}
}

float UInventoryComponent::GetItemCooldown(AActor* Target, const FName& ItemName) const
{
	auto ASC = UBaseFunctionLibrary::NativeGetAbilitySystemComponentFromActor(Target);
	if (ASC)
	{
		FUsableItemInfo* ItemInfo = ItemDataTable->FindRow<FUsableItemInfo>(ItemName, "");
		FGameplayEffectQuery Query = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(ItemInfo->CooldownTag.GetSingleTagContainer());
		TArray<TPair<float, float>> Pair = ASC->GetActiveEffectsTimeRemainingAndDuration(Query);
		if (Pair.IsEmpty()) return 0.f;
		return Pair[0].Key / Pair[0].Value;
	}
	return 0.f;
}
