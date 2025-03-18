// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UnlockSystemComponent.h"

#include "AbilitySystemComponent.h"
#include "BaseFunctionLibrary.h"
#include "GameplayAbilitySpecHandle.h"
#include "DataAsset/DataAsset_StartupKasane.h"
#include "DataAsset/DataAsset_UnlockAbility.h"

// Sets default values for this component's properties
UUnlockSystemComponent::UUnlockSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	AbilitySystemComponent = nullptr;
	static ConstructorHelpers::FObjectFinder<UDataAsset_UnlockAbility> UnlockAbilityObject(TEXT("/Game/_BP/DataAssets/DA_Kasane_UnlockData.DA_Kasane_UnlockData"));
	if (UnlockAbilityObject.Succeeded())
	{
		DataAsset_UnlockAbility = UnlockAbilityObject.Object.Get();
	}
}

void UUnlockSystemComponent::InitUnlockData(UAbilitySystemComponent* ASC, const FGameplayTagContainer& Tags)
{
	AbilitySystemComponent = ASC;
	UnlockedTags = Tags;
}

void UUnlockSystemComponent::ApplyUnlockData()
{
	check(DataAsset_UnlockAbility && AbilitySystemComponent);
	if (UnlockedTags.IsEmpty()) return;
	TArray<FGameplayAbilitySpecHandle> OutAbilityHandles;
	FUnlockData Data;
	for (auto& UnlockedTag : UnlockedTags)
	{
		if (DataAsset_UnlockAbility->FindUnlockDataByTag(UnlockedTag,Data))
		{
			AbilitySystemComponent->FindAllAbilitiesWithTags(OutAbilityHandles, Data.OverrideInputTag.GetSingleTagContainer());
			
			if (OutAbilityHandles.IsEmpty() == false && OutAbilityHandles[0].IsValid())
			{
				AbilitySystemComponent->ClearAbility(OutAbilityHandles[0]);
			}

			FGameplayAbilitySpec Spec(Data.OverrideAbility);
			Spec.SourceObject = AbilitySystemComponent->GetAvatarActor();
			Spec.Level = Data.Level;
			AbilitySystemComponent->GiveAbility(Spec);
		}
		UBaseFunctionLibrary::AddPlaygameTagToActor(AbilitySystemComponent->GetAvatarActor(), Data.UnlockTag);
	}

	OnUpdateUnlockData.Broadcast();
	
}


