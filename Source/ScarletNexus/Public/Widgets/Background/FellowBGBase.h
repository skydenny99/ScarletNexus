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

public:
	UFUNCTION()
	void Init(const float LeftFellowHp,const float RightFellowHp);
	
	UFUNCTION()
	void UpdateFellowLeftHp(const float LeftHp);

	UFUNCTION()
	void UpdateFellowRightHp(const float RightHp);
	
};
