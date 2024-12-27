// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/ANS_ApproachTarget.h"

#include "Character/Character_Kasane.h"
#include "Components/TargetTrackingSpringArmComponent.h"

void UANS_ApproachTarget::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                      float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (auto Character = Cast<ACharacter_Kasane>(MeshComp->GetOwner()))
	{
		UTargetTrackingSpringArmComponent* TrackingTargetComponent = Character->GetTargetTrackingComponent();
		if(TrackingTargetComponent && TrackingTargetComponent->GetCurrentTarget())
		{
			DesiredLocation = TrackingTargetComponent->GetCurrentTarget()->GetActorLocation();
			DesiredLocation.Z = Character->GetActorLocation().Z;
		}
		else
		{
			DesiredLocation = Character->GetActorLocation() + Character->GetActorForwardVector() * 500.f;
		}
	}
}

void UANS_ApproachTarget::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	AActor* Owner = MeshComp->GetOwner();
	if (Owner)
	{
		Owner->SetActorLocation(FMath::VInterpTo(Owner->GetActorLocation(), DesiredLocation, FrameDeltaTime, 1.f));
	}
}
