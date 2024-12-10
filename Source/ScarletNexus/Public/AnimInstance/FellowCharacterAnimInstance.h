// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/CharacterAnimInstance.h"
#include "FellowCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UFellowCharacterAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()
	public:


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockOn")
	FVector LookAtPos;
	
	
};
