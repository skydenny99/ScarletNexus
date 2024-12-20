// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/WidgetBase.h"
#include "AnnouncerBGBase.generated.h"

class UImage;
class UOverlay;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UAnnouncerBGBase : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UOverlay* Base;

	UPROPERTY(meta = (BindWidget))
	UImage* IMG_Face;

	UPROPERTY(meta = (BindWidget))
	UImage* LodingAnim;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text;
	
};
