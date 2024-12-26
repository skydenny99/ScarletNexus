// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "BaseType/BaseEnumType.h"
#include "BossUIBase.generated.h"

class UMaterialInstanceDynamic;
class UMaterial;
class UImage;
class UPaperSprite;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UBossUIBase : public UWidgetBase
{
	GENERATED_BODY()
	
private:
	float Percent;
	float PrevTopProgress;
	float BottomProgress;
	float AnimationSpeed;
	bool bIsActive;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	UMaterial* HpMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* BrainCrashMaterial;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<UPaperSprite*> DebuffMaterial;
	
	UPROPERTY()
	UMaterialInstanceDynamic* HpDynamicMaterialInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* BrainCrashDynamicMaterialInstance;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Boss_HealthGauge;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Boss_BrainCrashGauge;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Boss_Debuff_Icon;
	
public:
	//virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDebuff(EBaseDebuffType DebuffType = EBaseDebuffType::NONE);

	UFUNCTION(BlueprintCallable)
	void OnDamaged(const float SetPercent);
	
	UFUNCTION(BlueprintCallable)
	void UpdateHp(const float TopProgress, const float DeltaSec);

	UFUNCTION(BlueprintCallable)
	void UpdateBrainCrashGauge(const float Value);

	UFUNCTION()
	void OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* EnemyUIComponent) const override;
	
	UFUNCTION()
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};


