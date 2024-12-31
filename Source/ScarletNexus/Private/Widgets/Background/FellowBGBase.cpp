// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Background/FellowBGBase.h"
#include "Components/UI/PlayerUIComponent.h"
#include "Components/TextBlock.h"

void UFellowBGBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	T_LName->SetText(FText::FromString(TEXT("Hanabi Ichijo")));
	T_RName->SetText(FText::FromString(TEXT("Arashi Spring")));
}

void UFellowBGBase::InitLeft(const FString LName, const float LeftFellowHp)
{
	T_LName->SetText(FText::FromString(LName));
	T_LHealthPoint->SetText(FText::FromString(FString::FromInt(static_cast<int>(LeftFellowHp))));
	T_LHealthPoint_Max->SetText(FText::FromString(FString::FromInt(static_cast<int>(LeftFellowHp))));
}

void UFellowBGBase::InitRight(const FString RName, const float RightFellowHp)
{
	T_RName->SetText(FText::FromString(RName));
	T_RHealthPoint->SetText(FText::FromString(FString::FromInt(static_cast<int>(RightFellowHp))));
	T_RHealthPoint_Max->SetText(FText::FromString(FString::FromInt(static_cast<int>(RightFellowHp))));
}

void UFellowBGBase::InitLeftFellowHp(const float LeftFellowHp)
{
	T_LHealthPoint_Max->SetText(FText::FromString(FString::FromInt(static_cast<int>(LeftFellowHp))));
}

void UFellowBGBase::InitRightFellowHp(const float RightFellowHp)
{
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

void UFellowBGBase::OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const
{
	Super::OnOwningPlayerUIComponentInitialized(PlayerUIComponent);

	//PlayerUIComponent->OnFellowInit.AddDynamic(this,&UFellowBGBase::Init);
	PlayerUIComponent->OnUpdateFellowLeftHp.AddDynamic(this,&UFellowBGBase::UpdateFellowLeftHp);
	PlayerUIComponent->OnUpdateFellowRightHp.AddDynamic(this,&UFellowBGBase::UpdateFellowRightHp);
}
