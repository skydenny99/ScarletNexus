// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/ANS_GrabPsychObject.h"

#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"
#include "Actor/PsychokineticThrowableProp.h"
#include "Character/Character_Kasane.h"
#include "Character/EnemyCharacter/BaseEnemyCharacter.h"
#include "Components/PsychokinesisComponent.h"
#include "Components/TargetTrackingSpringArmComponent.h"

void UANS_GrabPsychObject::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                       float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (auto Character = Cast<ACharacter_Kasane>(MeshComp->GetOwner()))
	{
		PsychokinesisComponent = Character->GetPsychokinesisComponent();
		ThrowableProp = Cast<APsychokineticThrowableProp>(PsychokinesisComponent->GetPsychThrowableTarget());
		if (ThrowableProp)
		{
			ThrowableProp->OnStartGrab(
			UBaseFunctionLibrary::NativeActorHasTag(Character, BaseGameplayTags::Player_Status_SAS_Clone),
			true);
			AActor* TargetActor = Character->GetTargetTrackingComponent()->GetCurrentTarget();
			ThrowableProp->SetTarget(TargetActor);
			if(ABaseEnemyCharacter* EnemyCharacter = Cast<ABaseEnemyCharacter>(TargetActor))
			{
				ThrowableProp->SetTarget(EnemyCharacter->GetTargetVector());
			}
		}
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

void UANS_GrabPsychObject::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (PsychokinesisComponent && ThrowableProp)
	{
		PsychokinesisComponent->AttachPsychTargetToBone(ThrowableProp);
	}
}
