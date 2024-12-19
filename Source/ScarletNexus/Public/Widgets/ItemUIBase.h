// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "ItemUIBase.generated.h"

class UMaterial;
class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UItemUIBase : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	UMaterial* Progressbar;

	UPROPERTY()
	UMaterialInstanceDynamic* ProgressbarInstance;
	
	UPROPERTY(meta = (BindWidget))
	class UImage* Item_Progressbar;

public:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintCallable)
	void OnUseItem();
};
