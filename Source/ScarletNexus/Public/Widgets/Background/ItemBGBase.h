// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "ItemBGBase.generated.h"

class UPaperSprite;
class UTextBlock;
class UImage;
struct FConsumItemInfo;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UItemBGBase : public UWidgetBase
{
	GENERATED_BODY()

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

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	static int32 Side (const int Index,const int Lenght,const bool bIsLeft);

	UFUNCTION(BlueprintCallable)
	void UpdateBefore(const TArray<FConsumItemInfo>& Items, const int32 Middle, const bool bIsLeft);

	UFUNCTION(BlueprintCallable)
	void UpdateAfter(const TArray<FConsumItemInfo>& Items, const int32 Middle);

	UFUNCTION(BlueprintCallable)
	void Init(const TArray<FConsumItemInfo>& Items, const int32 Middle);
};
