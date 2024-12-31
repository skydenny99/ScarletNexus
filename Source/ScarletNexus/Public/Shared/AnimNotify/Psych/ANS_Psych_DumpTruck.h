// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_Psych_DumpTruck.generated.h"

class APsychokineticPropBase;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UANS_Psych_DumpTruck : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	APsychokineticPropBase* Truck;
	FVector StartLocation;
	FVector FallingLocation;

	UPROPERTY(EditAnywhere)
	int32 MovingTotalFrames;
	int32 CurrentFrames;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
