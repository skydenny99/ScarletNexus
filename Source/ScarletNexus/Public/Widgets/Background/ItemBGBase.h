// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "ItemBGBase.generated.h"

class UInventoryComponent;
struct FInventoryItemInfo;
class UPaperSprite;
class UTextBlock;
class UImage;
class UWidgetAnimation;
struct FConsumItemInfo;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UItemBGBase : public UWidgetBase
{
	GENERATED_BODY()
private:
	UPROPERTY(BlueprintReadOnly,meta=(AllowPrivateAccess=true))
	int32 CachedCurrentIndex;
	
protected:
	UPROPERTY()
	UMaterialInstance* MaterialInstance;
	
	UPROPERTY()
	UMaterialInstanceDynamic* LeftMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* LeftSwapMaterialInstance;
	
	UPROPERTY()
	UMaterialInstanceDynamic* MiddleMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* MiddleSwapMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* RightMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* RightSwapMaterialInstance;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* GlowMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* GlowMaterialInstance;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_ItemName;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_Left;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_Left_Swap;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_Middle;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_Middle_Swap;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_Right;

	UPROPERTY(meta = (BindWidget))
	UImage* Item_Right_Swap;

	UPROPERTY(meta = (BindWidget))
	UImage* Glow;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LeftQuantity;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MiddleQuantity;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RightQuantity;

	//UPROPERTY(Transient ,meta = (BindWidgetAnim))
	//UWidgetAnimation* SwapR;
	
	//UPROPERTY(Transient ,meta = (BindWidgetAnim))
	//UWidgetAnimation* SwapL;

public:
	virtual void NativeConstruct() override;

	UPROPERTY()
	UInventoryComponent* InventoryComponent;
	
	UFUNCTION()
	static int32 Side (const int Index,const int Lenght,const bool bIsLeft);

	UFUNCTION(BlueprintCallable)
	void UpdateBefore(int32 OldIndex , bool bIsLeft);
	
	UFUNCTION(BlueprintCallable)
	void UpdateAfter(int32 CurrentIndex);

	UFUNCTION(BlueprintCallable)
	void Init(int32 CurrentIndex);

	UFUNCTION(BlueprintCallable)
	void UpdateQuantity(int32 CurrentIndex);

	UFUNCTION(BlueprintCallable)
	void SetGlowVisibility(float Percent);

	UFUNCTION()
	void OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const override;
	
};
