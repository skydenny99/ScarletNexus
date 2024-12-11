// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialParameterCollection.h"
#include "Widgets/WidgetBase.h"
#include "BossUIBase.generated.h"

class UMaterialParameterCollection;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UBossUIBase : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UMaterialParameterCollection* MaterialParameterCollection;

public:
	//FName GetParameterName();
	//void TakeDamage(float DamageAmount);
};
