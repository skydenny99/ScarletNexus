// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/DataAsset_StartupBase.h"
#include "AbilitySystemComponent.h"

void UDataAsset_StartupBase::GiveStartupAbilities(UAbilitySystemComponent* ASC, int32 Level)
{
	check(ASC);

	for (const auto& AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec Spec(AbilityClass);
		Spec.SourceObject = ASC->GetAvatarActor();
		Spec.Level = Level;
		ASC->GiveAbility(Spec);
	}
}
