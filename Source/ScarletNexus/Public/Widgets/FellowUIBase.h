// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "FellowUIBase.generated.h"

class UImage;
class UMaterial;
class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UFellowUIBase : public UWidgetBase
{
	GENERATED_BODY()
private:
	float AnimSpeed;
	float LeftHpPercent;
	float LPrevTopProgress;
	float LBottomProgress;
	float RightHpPercent;
	float RBottomProgress;
	float RPrevTopProgress;
	bool bIsActive;
protected:
	UPROPERTY(EditDefaultsOnly)
	UMaterial* HpMaterial;

	UPROPERTY()
	UMaterialInstanceDynamic* RightMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* LeftMaterialInstance;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Right_Hp;

	UPROPERTY(meta = (BindWidget))
	UImage* Left_Hp;

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BluePrintCallable)
	void OnDamagedRFellow(const float SetPercent);

	UFUNCTION(BluePrintCallable)
	void OnDamagedLFellow(const float SetPercent);

	UFUNCTION()
	void UpdateRightHp(const float TopProgress,const float DeltaSec);

	UFUNCTION()
	void UpdateLeftHp(const float TopProgress,const float DeltaSec);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
