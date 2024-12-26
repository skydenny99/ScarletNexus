// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Background/PlayerBGBase.h"

#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetTextLibrary.h"
#include "Components/UI/PlayerUIComponent.h"

void UPlayerBGBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	//TODO::Incoding problem
	FString A = UKismetSystemLibrary::MakeLiteralString("Kasane Randle");
	T_PlayerName->SetText(UKismetTextLibrary::Conv_StringToText(A.TrimQuotes()));
	
	T_HealthPoint->SetText(FText::FromString(FString::FromInt(1234)));
	T_HealthPoint_Max->SetText(FText::FromString(FString::FromInt(1500)));
}

void UPlayerBGBase::UpdateHp(float HealthPoint)
{
	T_HealthPoint->SetText(FText::FromString(FString::FromInt(static_cast<int>(HealthPoint))));
}

void UPlayerBGBase::Init(const FString& Name, const float HpMax)
{
	T_PlayerName->SetText(FText::FromString(Name));
	T_HealthPoint->SetText(FText::FromString(FString::FromInt(HpMax)));
	T_HealthPoint_Max->SetText(FText::FromString(FString::FromInt(HpMax)));
}

void UPlayerBGBase::OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const
{
	Super::OnOwningPlayerUIComponentInitialized(PlayerUIComponent);

	PlayerUIComponent->OnDebuffChanged.AddDynamic(this,&UPlayerBGBase::UpdateDebuff);
	PlayerUIComponent->OnInitPlayer.AddDynamic(this,&UPlayerBGBase::Init);
	PlayerUIComponent->OnPlayerHpChanged.AddDynamic(this,&UPlayerBGBase::UpdateHp);
}