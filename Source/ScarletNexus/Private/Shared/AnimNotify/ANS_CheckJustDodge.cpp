// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/ANS_CheckJustDodge.h"

#include "BaseDebugHelper.h"
#include "Character/Character_Kasane.h"
#include "Components/ComboSystemComponent.h"

void UANS_CheckJustDodge::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                      float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	Kasane = Cast<ACharacter_Kasane>(MeshComp->GetOwner());
	bIsJustDodged = false;
}

void UANS_CheckJustDodge::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	if (bIsJustDodged == false)
	{
		if (Kasane)
		{
			bIsJustDodged = Kasane->GetComboSystemComponent()->CheckJustDodge();
		}
	}
}
