// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Background/FellowBGBase.h"

#include "Components/TextBlock.h"

void UFellowBGBase::Init(const FString LName, const float LeftFellowHp, const FString RName, const float RightFellowHp)
{
	T_LName->SetText(FText::FromString(LName));
	T_LHealthPoint->SetText(FText::FromString(FString::FromInt(static_cast<int>(LeftFellowHp))));
	T_LHealthPoint_Max->SetText(FText::FromString(FString::FromInt(static_cast<int>(LeftFellowHp))));

	T_RName->SetText(FText::FromString(RName));
	T_RHealthPoint->SetText(FText::FromString(FString::FromInt(static_cast<int>(RightFellowHp))));
	T_RHealthPoint_Max->SetText(FText::FromString(FString::FromInt(static_cast<int>(RightFellowHp))));
}

void UFellowBGBase::UpdateFellowLeftHp(const float LeftHp)
{
	T_LHealthPoint->SetText(FText::FromString(FString::FromInt(static_cast<int>(LeftHp))));
}

void UFellowBGBase::UpdateFellowRightHp(const float RightHp)
{
	T_RHealthPoint->SetText(FText::FromString(FString::FromInt(static_cast<int>(RightHp))));
}
