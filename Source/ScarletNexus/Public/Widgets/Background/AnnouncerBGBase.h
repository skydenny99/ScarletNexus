// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "AnnouncerBGBase.generated.h"

class UImage;
class UOverlay;
class UTextBlock;
class UMaterial;
class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UAnnouncerBGBase : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<UMaterial*> Textures;
	
	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstance;
	
	UPROPERTY(meta = (BindWidget))
	UImage* IMG_Face;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* T_Announce;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateAnnounce(UMaterial* Face, const FString InputText);

	UFUNCTION()
	void OnOwningPlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent) const override;
};
