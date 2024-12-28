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

USTRUCT(BlueprintType)
struct FCharacterMontageSet
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UAnimMontage* LeftChargeAnimMontage;
	
	UPROPERTY(EditAnywhere)
	UAnimMontage* RightChargeAnimMontage;
	
	UPROPERTY(EditAnywhere)
	FMontageArray PsychAttackAnimMontages;
};
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UDataAsset_PsychMontage : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category= "PsychObject")
	TMap<EPsychType, FMontageArray> ObjectGroundAnimMontages;
	
	UPROPERTY(EditAnywhere, Category= "PsychObject")
	TArray<UAnimMontage*> ObjectAerialAnimMontages;

	UPROPERTY(EditAnywhere, Category= "PsychObject")
	UAnimMontage* ObjectJustDodgeMontage;
	
	UPROPERTY(EditAnywhere, Category= "Character")
	TMap<EPsychType, FCharacterMontageSet> CharacterGroundAnimMontageSets;
};
