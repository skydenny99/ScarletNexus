// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnlockSystemComponent.generated.h"


class UAbilitySystemComponent;
struct FUnlockData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCARLETNEXUS_API UUnlockSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	TArray<FUnlockData*> UnlockDatas;
	UAbilitySystemComponent* AbilitySystemComponent;
	
public:	
	// Sets default values for this component's properties
	UUnlockSystemComponent();

	void InitUnlockData(UAbilitySystemComponent* ASC, TArray<FUnlockData*> InUnlockDatas);
	void ApplyUnlockData();
};
