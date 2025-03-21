// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStructType.generated.h"

class UPaperSprite;
struct FColor;

USTRUCT(BlueprintType)
struct FSASData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UPaperSprite* Sprite;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UPaperSprite* BackSprite;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FColor Color;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float Percent;
};

UENUM(BlueprintType)
enum class EBaseAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};


USTRUCT(BlueprintType)
struct FConsumItemInfo
{
	GENERATED_BODY()

	//sprite
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor Color;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Percentage;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInstance* ItemMaterial;
};
