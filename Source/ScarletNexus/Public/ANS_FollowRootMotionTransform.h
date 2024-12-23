// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_FollowRootMotionTransform.generated.h"

class ACharacter_Kasane;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UANS_FollowRootMotionTransform : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	USkeletalMeshComponent* SourceMesh;

	FVector OriginRelativeLocation;
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
};
