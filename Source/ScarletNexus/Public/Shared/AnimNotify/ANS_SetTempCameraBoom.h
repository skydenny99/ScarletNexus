// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_SetTempCameraBoom.generated.h"

class ACharacter_Kasane;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UANS_SetTempCameraBoom : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	ACharacter_Kasane *Character;
	UPROPERTY(EditAnywhere)
	FVector DesiredTargetOffset;
	UPROPERTY(EditAnywhere)
	FVector DesiredSocketOffset;
	UPROPERTY(EditAnywhere)
	float DesiredTargetArmLength;
	
	FVector OriginTargetOffset;
	FVector OriginSocketOffset;
	float OriginTargetArmLength;

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
