// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "BossBGBase.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UBossBGBase : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BossName;

public:
	UFUNCTION(BlueprintCallable)
	void InitBossName(const FString Name);
	
	UFUNCTION()
	void OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* EnemyUIComponent) const override;
};
