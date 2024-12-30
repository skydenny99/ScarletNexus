// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "ItemUIBase.generated.h"

class UMaterial;
class UMaterialInstanceDynamic;
class UImage;
struct FConsumItemInfo;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UItemUIBase : public UWidgetBase
{
	GENERATED_BODY()
private:
	FTimerHandle ItemCoolTimerHandle;
	
protected:
	UPROPERTY(EditAnywhere)
	UMaterial* GaugeMaterial;
	
	UPROPERTY()
	UMaterialInstanceDynamic* GaugeMaterialInstance;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Item_Progressbar;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterial* ArrowMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* ArrowMaterialInstance;
	
	UPROPERTY(meta = (BindWidget))
	UImage* DownArrow_B;
	
public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void UpdateGauge(const FColor& Color, float Percent);

	UFUNCTION()
	virtual void OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const override;
};
