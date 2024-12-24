// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Background/AnnouncerBGBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "kismet/KismetMaterialLibrary.h"

void UAnnouncerBGBase::UpdateFace(UMaterial* Face)
{
	MaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(),Face);
	IMG_Face->SetBrushFromMaterial(MaterialInstance);
}

void UAnnouncerBGBase::UpdateAnnounce(const FString InputText)
{
	T_Announce->SetText(FText::FromString(InputText));
}
