// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/DataAsset_StartupKasane.h"
#include "AbilitySystemComponent.h"

void UDataAsset_StartupKasane::GiveStartupAbilities(UAbilitySystemComponent* ASC, int32 Level)
{
	Super::GiveStartupAbilities(ASC, Level);
	GiveUnlockAbilities(ASC, Level);
}

void UDataAsset_StartupKasane::GiveUnlockAbilities(UAbilitySystemComponent* ASC, int32 Level)
{
	FGameplayTagContainer TargetInputTags;
	TArray<FUnlockData*> TargetUnlockDatas;
	for (const FGameplayTag& UnlockTag : UnlockTags)
	{
		auto Tmp = UnlockDatas.Find(UnlockTag);
		TargetUnlockDatas.AddUnique(Tmp);
		TargetInputTags.AddTag(Tmp->OverrideTargetTag);
	}

	TArray<FGameplayAbilitySpecHandle> OutAbilityHandles;

	if (TargetInputTags.IsEmpty()) return;
	ASC->FindAllAbilitiesWithTags(OutAbilityHandles, TargetInputTags);

	for (const auto& Handle : OutAbilityHandles)
	{
		if (Handle.IsValid())
		{
			ASC->ClearAbility(Handle);
		}
	}

	for (const auto& UnlockData : TargetUnlockDatas)
	{
		FGameplayAbilitySpec Spec(UnlockData->OverrideAbility);
		Spec.SourceObject = ASC->GetAvatarActor();
		Spec.Level = Level;
		ASC->GiveAbility(Spec);
	}
}
