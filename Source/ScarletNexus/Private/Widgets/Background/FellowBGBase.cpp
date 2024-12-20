// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Background/FellowBGBase.h"

#include "Components/TextBlock.h"

void UFellowBGBase::Init(const float LeftFellowHp,const float RightFellowHp)
{
	T_LHealthPoint->SetText(FText::FromString(FString::SanitizeFloat(LeftFellowHp)));
	T_LHealthPoint_Max->SetText(FText::FromString(FString::SanitizeFloat(LeftFellowHp)));
	
	T_RHealthPoint->SetText(FText::FromString(FString::SanitizeFloat(RightFellowHp)));
	T_RHealthPoint_Max->SetText(FText::FromString(FString::SanitizeFloat(RightFellowHp)));
}

void UFellowBGBase::UpdateFellowLeftHp(const float LeftHp)
{
	T_LHealthPoint->SetText(FText::FromString(FString::SanitizeFloat(LeftHp)));
}

void UFellowBGBase::UpdateFellowRightHp(const float RightHp)
{
	T_RHealthPoint->SetText(FText::FromString(FString::SanitizeFloat(RightHp)));
}
