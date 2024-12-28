// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "SASManageComponent.generated.h"


class UDataAsset_SASAbility;
class ACharacter_Kasane;
class UBaseAbilitySystemComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCARLETNEXUS_API USASManageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USASManageComponent();

protected:
	UPROPERTY()
	ACharacter_Kasane* Kasane;
	
	UPROPERTY()
	UBaseAbilitySystemComponent* BaseAbilitySystemComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	UDataAsset_SASAbility* AbilityAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	TArray<FGameplayTag> CurrentSASAbilityTags;
	TMap<FGameplayTag, FGameplayAbilitySpec> AbilitySpecs;
	
	void ToggleSASAbility(FGameplayTag InInputTag);
	void CancelAllSASAbilities();

public:
	void InitReferences(ACharacter_Kasane* InKasane);
	void GrantSASAbilites(int32 Level = 1);
	void OnSASInputTriggered(FGameplayTag InInputTag);

};
