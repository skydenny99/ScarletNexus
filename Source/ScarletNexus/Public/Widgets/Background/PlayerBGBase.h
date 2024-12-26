// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "BaseType/BaseEnumType.h"
#include "PlayerBGBase.generated.h"

class UPaperSprite;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UPlayerBGBase : public UWidgetBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)	
	TArray<UPaperSprite*> SpriteImg;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_PlayerName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_HealthPoint;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_HealthPoint_Max;
public:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateDebuff(EBaseDebuffType Debuff = EBaseDebuffType::NONE);

	UFUNCTION()
	void Init(const FString& Name, const float HpMax);
	
	UFUNCTION(BlueprintCallable)
	void UpdateHp(float HealthPoint);

	UFUNCTION()
	void OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const override;
};



