// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/DataAsset_StartupKasane.h"
#include "AbilitySystemComponent.h"
#include "Components/UnlockSystemComponent.h"

void UDataAsset_StartupKasane::GiveStartupAbilities(UAbilitySystemComponent* ASC, int32 Level)
{
	Super::GiveStartupAbilities(ASC, Level);
	GiveUnlockAbilities(ASC);
}

void UDataAsset_StartupKasane::GiveUnlockAbilities(UAbilitySystemComponent* ASC)
{
	UUnlockSystemComponent* UnlockSystemComponent = Cast<UUnlockSystemComponent>(ASC->GetAvatarActor()->FindComponentByClass(UUnlockSystemComponent::StaticClass()));
	check(UnlockSystemComponent);
	UnlockSystemComponent->InitUnlockData(ASC, UnlockTags);
	UnlockSystemComponent->ApplyUnlockData();
}
