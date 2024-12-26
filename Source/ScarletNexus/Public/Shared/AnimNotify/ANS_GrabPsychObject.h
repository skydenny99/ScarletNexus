// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_GrabPsychObject.generated.h"

class UPsychokinesisComponent;
class APsychokineticThrowableProp;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UANS_GrabPsychObject : public UAnimNotifyState
{
	GENERATED_BODY()

	UPROPERTY()
	UPsychokinesisComponent* PsychokinesisComponent;

	UPROPERTY()
	APsychokineticThrowableProp* ThrowableProp;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
