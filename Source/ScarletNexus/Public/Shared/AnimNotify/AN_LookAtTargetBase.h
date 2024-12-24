// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_LookAtTargetBase.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UAN_LookAtTargetBase : public UAnimNotify
{
	GENERATED_BODY()
protected:
	virtual AActor* GetTargetActor() const {return nullptr;}

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
