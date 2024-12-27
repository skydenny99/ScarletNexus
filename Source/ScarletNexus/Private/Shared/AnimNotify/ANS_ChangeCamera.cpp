// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/ANS_ChangeCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Character/Character_Kasane.h"

void UANS_ChangeCamera::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                    const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (ACharacter_Kasane* Character = Cast<ACharacter_Kasane>(MeshComp->GetOwner()))
	{
		Character->ChangeCamera(false);
	}
	
}

void UANS_ChangeCamera::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                  const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (ACharacter_Kasane* Character = Cast<ACharacter_Kasane>(MeshComp->GetOwner()))
	{
		Character->ChangeCamera(true);
	}
}
