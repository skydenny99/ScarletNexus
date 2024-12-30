// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FUsableItemInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> ItemGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* ItemMaterial;
	
};

USTRUCT()
struct FInventoryItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FName ItemName;

	UPROPERTY(EditDefaultsOnly)
	int32 CurrentCount;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxCount;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCARLETNEXUS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UDataTable* ItemDataTable;

	UPROPERTY(EditDefaultsOnly)
	TArray<FInventoryItemInfo> Inventory;

	int32 CurrentIndex = 0;

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	TArray<FInventoryItemInfo> GetInventoryItems() const {return Inventory;}

	FUsableItemInfo GetItemInfo(const FName& ItemName) const;
	bool HasItem(const FName& ItemName, FInventoryItemInfo& FoundItemInfo) const;
	void ChangeIndex(bool InIsLeft);

	UFUNCTION(BlueprintCallable, category="Inventory")
	void UseCurrentSelectedItem(AActor* Target);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	void UseItemByName(AActor* Target, const FName& ItemName);
};
