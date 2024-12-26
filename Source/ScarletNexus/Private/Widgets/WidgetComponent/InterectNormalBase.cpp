// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WidgetComponent/InterectNormalBase.h"

#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UInterectNormalBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitClickSprite(true);
	DenyOverlay->SetVisibility(ESlateVisibility::Collapsed);
}

void UInterectNormalBase::PlayBlinkAnim()
{
	PlayAnimation(Blink);
}

void UInterectNormalBase::UpdateDeny(bool bIsDeny)
{
	if (bIsDeny)
	{
		DenyOverlay->SetVisibility(ESlateVisibility::Visible);
		ButtonFrame_Inner_Full->SetColorAndOpacity(FColor::FromHex("333333FF"));
	}
	else
	{
		DenyOverlay->SetVisibility(ESlateVisibility::Collapsed);
		ButtonFrame_Inner_Full->SetColorAndOpacity(FColor::White);
	}
}