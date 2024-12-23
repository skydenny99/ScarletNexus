// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_FollowRootMotionTransform.h"

#include "BaseDebugHelper.h"
#include "Character/Character_Kasane.h"
#include "Components/PsychokinesisComponent.h"

void UANS_FollowRootMotionTransform::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                                 float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	auto Character = Cast<ACharacter_Kasane>(MeshComp->GetOwner());
	if (Character)
	{
		SourceMesh = Character->GetPsychokinesisComponent()->GetPsychSkeletalMesh();
		OriginRelativeLocation = Character->GetActorLocation();
	}
}

void UANS_FollowRootMotionTransform::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	//MeshComp->SetRelativeLocation(OriginRelativeLocation);
}

void UANS_FollowRootMotionTransform::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	auto Character = Cast<ACharacter_Kasane>(MeshComp->GetOwner());
	if (Character)
	{
		FVector Temp = MeshComp->GetBoneLocation("WeaponRoot", EBoneSpaces::Type::WorldSpace);
		FVector NewLocation = FVector(-Temp.Z, Temp.Y, Temp.Y);
		Character->SetActorLocation(OriginRelativeLocation - (Temp - MeshComp->GetComponentLocation()));
	}
}
