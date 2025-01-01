// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WidgetComponent/InterectNormalBase.h"

#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/UI/PropUIComponent.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UInterectNormalBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitClickSprite(true);
	DenyOverlay->SetVisibility(ESlateVisibility::Collapsed);

	/*PsychInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), PsychMaterial);
	PsychGauge->SetBrushFromMaterial(PsychInstance);
	PsychInstance->SetScalarParameterValue("Percent",0.0f);
	
	PsychBlinkInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), PsychBlinkMaterial);
	PsychBlinkInstance->SetScalarParameterValue("isActivate",1.0f);*/
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

void UInterectNormalBase::OnOwningPropUIComponentInitialized(UPropUIComponent* PropUIComponent) const
{
	Super::OnOwningPropUIComponentInitialized(PropUIComponent);

	PropUIComponent->OnPropInit.AddDynamic(this,&UInterectNormalBase::InitClickSprite);
	PropUIComponent->OnDenyed.AddDynamic(this,&UInterectNormalBase::UpdateDeny);
	PropUIComponent->OnPlayedBlinkAnimation.AddDynamic(this,&UInterectNormalBase::PlayBlinkAnim);
}
