// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PsychokinesisComponent.h"
#include "Engine/DataAsset.h"
#include "DataAsset_PsychMontage.generated.h"

USTRUCT(BlueprintType)
struct FMontageArray
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> AnimMontages;
};
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UDataAsset_PsychMontage : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TMap<EPsychType, FMontageArray> GroundAnimMontages;
	
	UPROPERTY(EditAnywhere)
	TArray<UAnimMontage*> AerialAnimMontages;
};
