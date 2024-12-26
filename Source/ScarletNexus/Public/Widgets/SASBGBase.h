// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "SASBGBase.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API USASBGBase : public UWidgetBase
{
	GENERATED_BODY()

private:
	bool bisSwitch = false;
	
protected:
	UPROPERTY(meta = (BindWidget))
    UImage* Key_L;

	UPROPERTY(meta = (BindWidget))
	UImage* Deck1;

	UPROPERTY(meta = (BindWidget))
	UImage* DeckActive_L;

	UPROPERTY(meta = (BindWidget))
	UImage* Deck1_Activate;


	UPROPERTY(meta = (BindWidget))
	UImage* Key_R;

	UPROPERTY(meta = (BindWidget))
	UImage* Deck2;

	UPROPERTY(meta = (BindWidget))
	UImage* DeckActive_R;

	UPROPERTY(meta = (BindWidget))
	UImage* Deck2_Activate;

	UPROPERTY(meta = (BindWidget))
	UImage* SwitchLight;

public:
	UFUNCTION(BlueprintCallable)
	void OnToggleCtrl();

	UFUNCTION(BlueprintCallable)
 	void OnToggleAlt();

	UFUNCTION(BlueprintCallable)
	void OnToggleSwitch();

	UFUNCTION()
	void OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const override;
};
