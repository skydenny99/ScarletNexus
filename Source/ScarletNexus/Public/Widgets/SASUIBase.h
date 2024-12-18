// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "SASUIBase.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API USASUIBase : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "SASMat")
	UMaterial* SAS_L;

	UPROPERTY(EditDefaultsOnly, Category = "SASMat")
	UMaterial* SAS_R;

	UPROPERTY(EditDefaultsOnly, Category = "SASMat")
	UMaterial* SAS_T;

	UPROPERTY(EditDefaultsOnly, Category = "SASMat")
	UMaterial* SAS_B;

	
	UPROPERTY(meta = (BindWidget))
	UImage* IMG_SAS_Left;

	UPROPERTY(meta = (BindWidget))
	UImage* L_OutCircle;

	UPROPERTY(meta = (BindWidget))
	UImage* L_InCircle;

	
	UPROPERTY(meta = (BindWidget))
	UImage* IMG_SAS_Right;

	UPROPERTY(meta = (BindWidget))
	UImage* R_OutCircle;

	UPROPERTY(meta = (BindWidget))
	UImage* R_InCircle;

	
	UPROPERTY(meta = (BindWidget))
	UImage* IMG_SAS_Top;

	UPROPERTY(meta = (BindWidget))
	UImage* T_OutCircle;

	UPROPERTY(meta = (BindWidget))
	UImage* T_InCircle;

	
	UPROPERTY(meta = (BindWidget))
	UImage* IMG_SAS_Bottom;

	UPROPERTY(meta = (BindWidget))
	UImage* B_OutCircle;

	UPROPERTY(meta = (BindWidget))
	UImage* B_InCircle;

public:
	virtual void NativeOnInitialized() override;
};
