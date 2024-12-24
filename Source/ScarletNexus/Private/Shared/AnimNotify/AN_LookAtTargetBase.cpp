// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/AN_LookAtTargetBase.h"

#include "Kismet/KismetMathLibrary.h"

void UAN_LookAtTargetBase::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                  const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (const AActor* Target = GetTargetActor())
	{
		AActor* Owner = MeshComp->GetOwner();
		FRotator NewRot = UKismetMathLibrary::FindLookAtRotation(Owner->GetActorLocation(), Target->GetActorLocation());
		NewRot = FRotator(0, NewRot.Yaw, 0);
		Owner->SetActorRotation(NewRot);
	}
}
