// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "BossUIBase.generated.h"

class UMaterialInstanceDynamic;
class UMaterialInstance;
class UImage;
class UTexture2D;
class UPaperSprite;
struct FSlateBrush;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UBossUIBase : public UWidgetBase
{
	GENERATED_BODY()

public:
	//UBossUIBase();
	
private:
	float CurrentHp;
	float MaxHp;
	//FSlateBrush A;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* HpMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* StunMaterial;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<UPaperSprite*> DebuffMaterial;
	
	UPROPERTY()
	UMaterialInstanceDynamic* HpMaterialDynamicInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* StunMaterialDynamicInstance;

	/*UPROPERTY()
	TArray<UPaperSprite*> DebuffMaterialDynamicInstance;*/
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Boss_HealthGauge;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Boss_StunGauge;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* Boss_Debuff_Icon;
	
public:
	virtual void NativeOnInitialized() override;

	void UpdateHp(float Value);
	void UpdateStunGauge(float Value);
	void UpdateDebuff(int Enum);
	
	void TakeDamage(float DamageAmount) { CurrentHp = (CurrentHp-DamageAmount)/MaxHp; }
};
