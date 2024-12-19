// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStructType.generated.h"

class UPaperSprite;
struct FColor;

USTRUCT(BlueprintType)
struct FSASData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UPaperSprite* Sprite;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FColor Color;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float Percent;
};