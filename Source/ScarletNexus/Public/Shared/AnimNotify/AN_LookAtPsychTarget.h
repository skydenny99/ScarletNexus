// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/AnimNotify/AN_LookAtTargetBase.h"
#include "AN_LookAtPsychTarget.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UAN_LookAtPsychTarget : public UAN_LookAtTargetBase
{
	GENERATED_BODY()
protected:
	virtual AActor* GetTargetActor(AActor* Owner) const override;
};
