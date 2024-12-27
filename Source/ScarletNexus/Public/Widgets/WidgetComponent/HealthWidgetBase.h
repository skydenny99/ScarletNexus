// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseType/BaseEnumType.h"
#include "Widgets/WidgetBase.h"
#include "HealthWidgetBase.generated.h"

class UPaperSprite;
class UImage;
class UMaterial;
class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UHealthWidgetBase : public UWidgetBase
{
	GENERATED_BODY()
private:
	float AnimSpeed;
	float PrevTopProgress;
	float BottomProgress;
	float Percent;
	bool bIsActive;
protected:
	UPROPERTY(EditDefaultsOnly)
	UMaterial* HpMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* BrainCrashMaterial;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TArray<UPaperSprite*> DebuffSprite;
	
	UPROPERTY()
	UMaterialInstanceDynamic* HpMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* BrainCrashMaterialInstance;
	
	UPROPERTY(meta = (BindWidget))
	UImage* HealthGauge;

	UPROPERTY(meta = (BindWidget))
	UImage* StunGauge;

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void SetHealthGauge(const float SetPercent);

	UFUNCTION(BlueprintCallable)
	void UpdateBrainCrashGauge(const float Percent);

	UFUNCTION()
	void UpdateHealthGauge(const float TopProgress, const float DeltaSec);

	UFUNCTION()
	void OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* EnemyUIComponent) const override;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
