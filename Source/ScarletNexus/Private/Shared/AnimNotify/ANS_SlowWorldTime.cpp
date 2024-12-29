// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/ANS_SlowWorldTime.h"

#include "BaseDebugHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/TimeControlSubsystem.h"

void UANS_SlowWorldTime::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	auto TimeSubSystem = MeshComp->GetWorld()->GetSubsystem<UTimeControlSubsystem>();
	if (TimeSubSystem)
	{
		TimeSubSystem->SetupWorldTimeDilation(FName("SlowMotion"), TargetTimeDilation);
//		UGameplayStatics::SetGlobalTimeDilation(MeshComp->GetOwner(), TargetTimeDilation);
	}
}

void UANS_SlowWorldTime::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (auto TimeSubSystem = MeshComp->GetWorld()->GetSubsystem<UTimeControlSubsystem>())
	{
		TimeSubSystem->ReleaseWorldTimeDilation(FName("SlowMotion"));
	// UGameplayStatics::SetGlobalTimeDilation(MeshComp->GetOwner(), 1.f);
	}
}
