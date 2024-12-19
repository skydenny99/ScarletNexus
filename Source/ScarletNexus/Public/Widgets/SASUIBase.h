// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "SASUIBase.generated.h"

class UMaterialInstanceDynamic;
class UMaterial;
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

	UPROPERTY(EditDefaultsOnly, Category = "SASMat")
	UMaterial* SAS_Gauge;
	
	UPROPERTY()
	UMaterialInstanceDynamic* SAS_L_Dynamic;

	UPROPERTY()
	UMaterialInstanceDynamic* SAS_R_Dynamic;

	UPROPERTY()
	UMaterialInstanceDynamic* SAS_T_Dynamic;

	UPROPERTY()
	UMaterialInstanceDynamic* SAS_B_Dynamic;

	UPROPERTY()
	UMaterialInstanceDynamic* SAS_Gauge_Dynamic;
	
	UPROPERTY(meta = (BindWidget))
	UImage* L_Simbol;

	UPROPERTY(meta = (BindWidget))
	UImage* L_Gauge;

	
	UPROPERTY(meta = (BindWidget))
	UImage* R_Simbol;

	UPROPERTY(meta = (BindWidget))
	UImage* R_Gauge;

	
	UPROPERTY(meta = (BindWidget))
	UImage* T_Simbol;

	UPROPERTY(meta = (BindWidget))
	UImage* T_Gauge;

	
	UPROPERTY(meta = (BindWidget))
	UImage* B_Simbol;

	UPROPERTY(meta = (BindWidget))
	UImage* B_Gauge;

public:
	virtual void NativeOnInitialized() override;
};
