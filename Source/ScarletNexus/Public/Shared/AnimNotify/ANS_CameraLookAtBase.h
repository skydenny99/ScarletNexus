// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_CameraLookAtBase.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UANS_CameraLookAtBase : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	AActor* Camera;
	virtual FVector GetLookAtTargetLocation(AActor* Owner) const {return FVector::ZeroVector;};

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
};
