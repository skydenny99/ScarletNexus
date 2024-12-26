// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/ANS_SlowWorldTime.h"
#include "Kismet/GameplayStatics.h"

void UANS_SlowWorldTime::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	UGameplayStatics::SetGlobalTimeDilation(MeshComp->GetOwner(), TargetTimeDilation);
}

void UANS_SlowWorldTime::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	UGameplayStatics::SetGlobalTimeDilation(MeshComp->GetOwner(), 1.f);
}
