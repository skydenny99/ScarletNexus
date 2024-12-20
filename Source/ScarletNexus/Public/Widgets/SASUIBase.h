// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "BaseType/BaseStructType.h"
#include "SASUIBase.generated.h"

class UPaperSprite;
class UMaterialInstanceDynamic;
class UMaterial;
class UImage;
struct FSASData;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API USASUIBase : public UWidgetBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "SASMat")
	UPaperSprite* SAS_L;

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

	UPROPERTY(VisibleAnywhere,meta = (BindWidget))
	UImage* L_Gauge;
	
	UPROPERTY(meta = (BindWidget))
	UImage* R_Gauge;
	
	UPROPERTY(meta = (BindWidget))
	UImage* T_Gauge;

	UPROPERTY(meta = (BindWidget))
	UImage* B_Gauge;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void InitSprite(const TArray<FSASData>& Data);

	UFUNCTION(BlueprintCallable)
	void InitTopGauge(const FColor Color,const float Percent);

	UFUNCTION(BlueprintCallable)
	void InitLeftGauge(const FColor Color,const float Percent);

	UFUNCTION(BlueprintCallable)
	void InitRightGauge(const FColor Color,const float Percent);

	UFUNCTION(BlueprintCallable)
	void InitBottomGauge(const FColor Color,const float Percent);
	
	UFUNCTION(BlueprintCallable)
	void UpdateTopGauge(const float Percent);

	UFUNCTION(BlueprintCallable)
	void UpdateLeftGauge(const float Percent);

	UFUNCTION(BlueprintCallable)
	void UpdateRightGauge(const float Percent);

	UFUNCTION(BlueprintCallable)
	void UpdateBottomGauge(const float Percent);

	//TODO void SwitchSAS();
};
