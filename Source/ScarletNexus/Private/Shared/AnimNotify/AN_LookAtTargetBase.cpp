// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/AN_LookAtTargetBase.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"

void UAN_LookAtTargetBase::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                  const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (const AActor* Target = GetTargetActor(MeshComp->GetOwner()))
	{
		AActor* Owner = MeshComp->GetOwner();
		FRotator NewRot = UKismetMathLibrary::FindLookAtRotation(Owner->GetActorLocation(), Target->GetActorLocation());
		NewRot = FRotator(0, NewRot.Yaw, 0);
		Owner->SetActorRotation(NewRot);
		if (bUpdateControlRotation)
		{
			if (ACharacter* Character = Cast<ACharacter>(Owner))
			{
				FRotator ContRot = Character->GetControlRotation();
				ContRot.Yaw = NewRot.Yaw;
				Character->GetController()->SetControlRotation(ContRot);
			}
		}
	}
}
