// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

class UPlayerUIComponent;
class UEnemyUIComponent;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* EnemyUIComponent);

	virtual void OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const;
	virtual void OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* EnemyUIComponent) const;
public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreateWidget(AActor* Enemy);
};
