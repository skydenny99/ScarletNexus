// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "UnlockSystemComponent.generated.h"

class UDataAsset_UnlockAbility;
DECLARE_MULTICAST_DELEGATE(FOnUpdateUnlockData);

class UAbilitySystemComponent;
struct FUnlockData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCARLETNEXUS_API UUnlockSystemComponent : public UActorComponent
{
	GENERATED_BODY()

	FGameplayTagContainer UnlockedTags;
	UPROPERTY()
	UDataAsset_UnlockAbility* DataAsset_UnlockAbility;
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	
public:
	FOnUpdateUnlockData OnUpdateUnlockData;
	// Sets default values for this component's properties
	UUnlockSystemComponent();

	void InitUnlockData(UAbilitySystemComponent* ASC, FGameplayTagContainer Tags);
	void ApplyUnlockData();
};
