// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Background/AnnouncerBGBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "kismet/KismetMaterialLibrary.h"
#include "components/UI/PlayerUIComponent.h"

void UAnnouncerBGBase::UpdateAnnounce(UMaterial* Face, const FString InputText)
{
	//Face
	MaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Face);
	IMG_Face->SetBrushFromMaterial(MaterialInstance);
	
	//Text
	T_Announce->SetText(FText::FromString(InputText));
}

void UAnnouncerBGBase::OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const
{
	Super::OnOwningPlayerUIComponentInitialized(PlayerUIComponent);

	PlayerUIComponent->OnUpdateAnnounce.AddDynamic(this,&UAnnouncerBGBase::UpdateAnnounce);
}
