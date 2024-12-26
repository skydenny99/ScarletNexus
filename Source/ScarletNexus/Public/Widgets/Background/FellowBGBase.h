// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "FellowBGBase.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UFellowBGBase : public UWidgetBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_LHealthPoint;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_LHealthPoint_Max;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_RHealthPoint;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_RHealthPoint_Max;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_LName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_RName;

public:
	UFUNCTION(BlueprintCallable)
	void Init(const FString LName, const float LeftFellowHp, const FString RName, const float RightFellowHp);
	
	UFUNCTION(BlueprintCallable)
	void UpdateFellowLeftHp(const float LeftHp);

	UFUNCTION(BlueprintCallable)
	void UpdateFellowRightHp(const float RightHp);

	UFUNCTION()
	void OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const override;
	
};
