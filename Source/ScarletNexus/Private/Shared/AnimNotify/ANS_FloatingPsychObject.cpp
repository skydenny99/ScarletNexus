// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/ANS_FloatingPsychObject.h"

#include "BaseDebugHelper.h"
#include "Actor/PsychokineticThrowableProp.h"
#include "Character/Character_Kasane.h"
#include "Components/PsychokinesisComponent.h"

void UANS_FloatingPsychObject::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (auto Character = Cast<ACharacter_Kasane>(MeshComp->GetOwner()))
	{
		ThrowableProp = Cast<APsychokineticThrowableProp>(Character->GetPsychokinesisComponent()->GetPsychTarget());
	}
}

void UANS_FloatingPsychObject::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	if (ThrowableProp)
	{
		ThrowableProp->FloatingTick(FrameDeltaTime);
	}
}
