// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "PlayerUIBase.generated.h"

class UMaterial;
class UImage;
class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UPlayerUIBase : public UWidgetBase
{
	GENERATED_BODY()
private:
	float AnimSpeed;
	float HpPercent;
	float HpPrevTopProgress;
	float HpBottomProgress;
	float PsychPercent;
	float PsychPrevTopProgress;
	float PsychBottomProgress;
	bool bIsActive;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	UMaterial* HpMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* PsychMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* HpMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* PsychMaterialInstance;
	
	UPROPERTY(meta = (BindWidget))
	UImage* PlayerHp;

	UPROPERTY(meta = (BindWidget))
	UImage* PsychArrow;

	UPROPERTY(meta = (BindWidget))
	UImage* PsychGauge;

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnDamaged(const float SetPercent);

	UFUNCTION(BlueprintCallable)
	void SetPsychkinesis(const float SetPercent);

	UFUNCTION()
	void UpdateHp(const float TopProgress,const float DeltaSec);

	UFUNCTION()
	void UpdatePsych(const float TopProgress,const float DeltaSec);

	UFUNCTION()
	virtual void OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};