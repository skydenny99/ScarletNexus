// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/ANS_CameraLookAtBase.h"

#include "Character/Character_Kasane.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UANS_CameraLookAtBase::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (ACharacter_Kasane* Kasane = Cast<ACharacter_Kasane>(MeshComp->GetOwner()))
	{
		Camera = Kasane->GetComboDirectCameraActor();
	}
}

void UANS_CameraLookAtBase::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                       float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	if (Camera)
	{
		FVector TargetLocation = GetLookAtTargetLocation(MeshComp->GetOwner());
		if (TargetLocation.IsNearlyZero() == false)
		{
			FRotator NewRot = UKismetMathLibrary::FindLookAtRotation(Camera->GetActorLocation(), TargetLocation);
			Camera->SetActorRotation(NewRot);
		}
	}
	
}

void UANS_CameraLookAtBase::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (ACharacter_Kasane* Kasane = Cast<ACharacter_Kasane>(MeshComp->GetOwner()))
	{
		Kasane->ResetComboDirectCameraSetting();
	}
}
