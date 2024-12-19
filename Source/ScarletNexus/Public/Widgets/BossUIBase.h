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
	float CurrentHp;
	float MaxHp;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	UMaterial* HpMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* StunMaterial;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<UPaperSprite*> DebuffMaterial;
	
	UPROPERTY()
	UMaterialInstanceDynamic* HpMaterialDynamicInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* StunMaterialDynamicInstance;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Boss_HealthGauge;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Boss_StunGauge;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Boss_Debuff_Icon;
	
public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable, Category = "CaculateFunction")
	void OnDamaged(const float Damage);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDebuff(EBaseDebuffType DebuffType);
	
	void UpdateHp(const float Value);

	UFUNCTION(BlueprintCallable)
	void UpdateStunGauge(const float Value);
};
