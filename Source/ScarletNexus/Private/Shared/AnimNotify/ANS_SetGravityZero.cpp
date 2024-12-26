// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/ANS_SetGravityZero.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UANS_SetGravityZero::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                      float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		Character->GetMovementComponent()->Velocity = FVector::ZeroVector;
		Character->GetCharacterMovement()->GravityScale = 0.f;
		Character->GetCharacterMovement()->MovementMode = MOVE_Flying;
	}
}

void UANS_SetGravityZero::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (ACharacter* Character = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		Character->GetCharacterMovement()->GravityScale = DefaultGravityScale;
		Character->GetCharacterMovement()->MovementMode = MOVE_Walking;
	}
}
