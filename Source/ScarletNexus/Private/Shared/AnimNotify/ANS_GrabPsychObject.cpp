// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/ANS_GrabPsychObject.h"

#include "Actor/PsychokineticThrowableProp.h"
#include "Character/Character_Kasane.h"
#include "Components/PsychokinesisComponent.h"

void UANS_GrabPsychObject::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                       float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (auto Character = Cast<ACharacter_Kasane>(MeshComp->GetOwner()))
	{
		PsychokinesisComponent = Character->GetPsychokinesisComponent();
		ThrowableProp = Cast<APsychokineticThrowableProp>(PsychokinesisComponent->GetPsychTarget());
	}
}

void UANS_GrabPsychObject::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                      float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	if (PsychokinesisComponent && ThrowableProp)
	{
		PsychokinesisComponent->UpdatePsychTargetLocation(ThrowableProp, FrameDeltaTime);
	}
}
