// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_SlowWorldTime.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UANS_SlowWorldTime : public UAnimNotifyState
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditAnywhere, Category = "Time")
	FName DilationName = FName("SlowMotion");
	
	UPROPERTY(EditAnywhere, Category = "Time")
	float TargetTimeDilation = 0.3f;
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
