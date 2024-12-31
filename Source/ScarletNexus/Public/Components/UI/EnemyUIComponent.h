// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

//Boss
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInitBossNameDelegate,FString,NewName);

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnBossHpChanged;
	
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangeDelegate OnBrainCrashChanged;

	//Boss
	UPROPERTY(BlueprintAssignable)
	FInitBossNameDelegate OnInitBossName;
};
