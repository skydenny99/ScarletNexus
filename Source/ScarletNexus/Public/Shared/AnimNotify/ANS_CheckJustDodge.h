// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_CheckJustDodge.generated.h"

class ACharacter_Kasane;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UANS_CheckJustDodge : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	bool bIsJustDodged;
	ACharacter_Kasane* Kasane;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

};
