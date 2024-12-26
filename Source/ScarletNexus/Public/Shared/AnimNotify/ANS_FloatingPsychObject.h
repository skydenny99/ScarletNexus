// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_FloatingPsychObject.generated.h"

class APsychokineticThrowableProp;
class ACharacter_Kasane;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UANS_FloatingPsychObject : public UAnimNotifyState
{
	GENERATED_BODY()

	UPROPERTY()
	APsychokineticThrowableProp* ThrowableProp;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	
};
