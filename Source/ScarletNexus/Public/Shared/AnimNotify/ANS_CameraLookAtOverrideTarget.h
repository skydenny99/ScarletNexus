// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shared/AnimNotify/ANS_CameraLookAtBase.h"
#include "ANS_CameraLookAtOverrideTarget.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UANS_CameraLookAtOverrideTarget : public UANS_CameraLookAtBase
{
	GENERATED_BODY()

protected:
	virtual FVector GetLookAtTargetLocation(AActor* Owner) const override;
};
