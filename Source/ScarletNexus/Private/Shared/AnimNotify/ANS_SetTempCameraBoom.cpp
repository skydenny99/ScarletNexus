// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/ANS_SetTempCameraBoom.h"

#include <filesystem>

#include "Character/Character_Kasane.h"
#include "Components/TargetTrackingSpringArmComponent.h"

void UANS_SetTempCameraBoom::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	Character = Cast<ACharacter_Kasane>(MeshComp->GetOwner());
	if (Character)
	{
		OriginSocketOffset = Character->GetTargetTrackingComponent()->SocketOffset;
		OriginTargetOffset = Character->GetTargetTrackingComponent()->TargetOffset;
		OriginTargetArmLength = Character->GetTargetTrackingComponent()->TargetArmLength;
		Character->GetTargetTrackingComponent()->SocketOffset = DesiredSocketOffset;
		Character->GetTargetTrackingComponent()->TargetOffset = DesiredTargetOffset;
		Character->GetTargetTrackingComponent()->TargetArmLength = DesiredTargetArmLength;
	}
}

void UANS_SetTempCameraBoom::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (Character)
	{
		Character->GetTargetTrackingComponent()->SocketOffset = OriginSocketOffset;
		Character->GetTargetTrackingComponent()->TargetOffset = OriginTargetOffset;
		Character->GetTargetTrackingComponent()->TargetArmLength = OriginTargetArmLength;
	}
}
