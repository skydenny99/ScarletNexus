// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "InterectNormalBase.generated.h"

class UImage;
class UOverlay;
class UPaperSprite;
class UWidgetAnimation;
class UMaterial;
class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UInterectNormalBase : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite,meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* Blink;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidgetAnim),Transient)
	UWidgetAnimation* Remove;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	TArray<UPaperSprite*> ClickPaperSprite;
	
	UPROPERTY()
	UMaterialInstanceDynamic* PsychInstance;

	UPROPERTY()
	UMaterialInstanceDynamic* PsychBlinkInstance;

	UPROPERTY(meta = (BindWidget))
	UImage* ButtonFrame_Inner_Full;

	UPROPERTY(meta = (BindWidget))
	UOverlay* DenyOverlay;
	
	/*
	UPROPERTY(EditDefaultsOnly)
	UMaterial* PsychMaterial;
	
	UPROPERTY(EditDefaultsOnly)
	UMaterial* PsychBlinkMaterial;

	UPROPERTY(meta = (BindWidget))
	UImage* PsychGauge;
	*/
	
	
public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent)
	void InitClickSprite(bool bIsNormal);

	UFUNCTION(BlueprintCallable)
	void PlayBlinkAnim();

	UFUNCTION(BlueprintCallable)
	void UpdateDeny(bool bIsDeny);

	virtual void OnOwningPropUIComponentInitialized(UPropUIComponent* PropUIComponent) const override;
};
