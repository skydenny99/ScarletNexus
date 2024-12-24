// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Background/BossBGBase.h"

#include "Components/TextBlock.h"

void UBossBGBase::InitBossName(const FString Name)
{
	BossName->SetText(FText::FromString(Name));
}
