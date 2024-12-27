// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponent.h"
#include "PropUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPropInitDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOneParamDelegate,bool,Newbool);

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UPropUIComponent : public UPawnExtensionComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOneParamDelegate OnPropInit;
	
	UPROPERTY(BlueprintAssignable)
	FOnPropInitDelegate OnPlayedBlinkAnimation;

	UPROPERTY(BlueprintAssignable)
	FOneParamDelegate OnDenyed;
};
