// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameFramework/GameModeBase.h"
#include "ScarletNexusGameMode.generated.h"


DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPercentValueChanged, float, Percent);

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API AScarletNexusGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	
	
public:
	UFUNCTION(BlueprintCallable)
	void BP_BindFunctionWithAttributeChangeDelegate(AActor* InActor, const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute, FOnPercentValueChanged OnPercentValueChanged);

};
