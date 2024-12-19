// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "BossUIBase.generated.h"

class UMaterialInstanceDynamic;
class UMaterial;
class UImage;
class UTexture2D;
class UPaperSprite;

UENUM(BlueprintType)
enum class EDebuffState : uint8
{
	BURN,
	OIL,
	SHOCK,
	WET,
	CONFUSE,
	NONE,
};


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
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UPaperSprite*> DebuffMaterial;

	UPROPERTY()
	TArray<UImage*> DebuffImage;  
	
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
	void OnDamaged(float Damage);

	UFUNCTION(BlueprintImplementableEvent)
	void SetBrush();
	
	void UpdateHp(float Value);
	void UpdateStunGauge(float Value);
	void UpdateDebuff(EDebuffState Debuff);
	
	void TakeDamage(float DamageAmount) { CurrentHp = (CurrentHp-DamageAmount)/MaxHp; }
};
