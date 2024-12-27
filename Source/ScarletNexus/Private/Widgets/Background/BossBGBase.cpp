// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Background/BossBGBase.h"
#include "Components/UI/EnemyUIComponent.h"
#include "Components/TextBlock.h"

void UBossBGBase::InitBossName(const FString Name)
{
	BossName->SetText(FText::FromString(Name));
}

void UBossBGBase::OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* EnemyUIComponent) const
{
	Super::OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	EnemyUIComponent->OnInitBossName.AddDynamic(this,&UBossBGBase::InitBossName);
}