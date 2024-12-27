// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_SetGravityZero.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UANS_SetGravityZero : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly)
	float DefaultGravityScale = 3.f;
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
