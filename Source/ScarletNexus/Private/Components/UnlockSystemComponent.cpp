// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UnlockSystemComponent.h"

#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpecHandle.h"
#include "DataAsset/DataAsset_StartupKasane.h"

// Sets default values for this component's properties
UUnlockSystemComponent::UUnlockSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	AbilitySystemComponent = nullptr;
}

void UUnlockSystemComponent::InitUnlockData(UAbilitySystemComponent* ASC, TArray<FUnlockData*> InUnlockDatas)
{
	AbilitySystemComponent = ASC;
	UnlockDatas = InUnlockDatas;
}

void UUnlockSystemComponent::ApplyUnlockData()
{
	check(AbilitySystemComponent);
	if (UnlockDatas.IsEmpty()) return;
	TArray<FGameplayAbilitySpecHandle> OutAbilityHandles;
	for (auto Data : UnlockDatas)
	{
		AbilitySystemComponent->FindAllAbilitiesWithTags(OutAbilityHandles, Data->OverrideTargetTag.GetSingleTagContainer());
		if (OutAbilityHandles.IsEmpty()) continue;
		
		if (OutAbilityHandles[0].IsValid())
		{
			AbilitySystemComponent->ClearAbility(OutAbilityHandles[0]);
		}

		FGameplayAbilitySpec Spec(Data->OverrideAbility);
		Spec.SourceObject = AbilitySystemComponent->GetAvatarActor();
		Spec.Level = Data->Level;
		AbilitySystemComponent->GiveAbility(Spec);
	}

	
}


