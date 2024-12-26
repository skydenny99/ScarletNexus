// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SASBGBase.h"
#include "Components/UI/PlayerUIComponent.h"
#include "Components/Image.h"

void USASBGBase::OnToggleCtrl()
{
	if (Key_L->GetColorAndOpacity() == FLinearColor::White)
	{
		Key_L->SetColorAndOpacity(FLinearColor::Black);
		Deck1->SetVisibility(ESlateVisibility::Hidden);
		DeckActive_L->SetVisibility(ESlateVisibility::Visible);
		Deck1_Activate->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Key_L->SetColorAndOpacity(FLinearColor::White);
		Deck1->SetVisibility(ESlateVisibility::Visible);
		DeckActive_L->SetVisibility(ESlateVisibility::Hidden);
		Deck1_Activate->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USASBGBase::OnToggleAlt()
{
	if (Key_R->GetColorAndOpacity() == FLinearColor::White)
	{
		Key_R->SetColorAndOpacity(FLinearColor::Black);
		Deck2->SetVisibility(ESlateVisibility::Hidden);
		DeckActive_R->SetVisibility(ESlateVisibility::Visible);
		Deck2_Activate->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Key_R->SetColorAndOpacity(FLinearColor::White);
		Deck2->SetVisibility(ESlateVisibility::Visible);
		DeckActive_R->SetVisibility(ESlateVisibility::Hidden);
		Deck2_Activate->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USASBGBase::OnToggleSwitch()
{
	if (bisSwitch == false)
	{
		bisSwitch = true;
		SwitchLight->SetRenderTranslation(FVector2D(37.0f,0.0f));
	}
	else
	{
		bisSwitch = false;
		SwitchLight->SetRenderTranslation(FVector2D(-37.0f,0.0f));
	}
	
}

void USASBGBase::OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const
{
	Super::OnOwningPlayerUIComponentInitialized(PlayerUIComponent);

	PlayerUIComponent->OnCtrlKeyDown.AddDynamic(this,&USASBGBase::OnToggleCtrl);
	PlayerUIComponent->OnAltKeyDown.AddDynamic(this,&USASBGBase::OnToggleAlt);
	PlayerUIComponent->OnXKeyDown.AddDynamic(this,&USASBGBase::OnToggleSwitch);
}
