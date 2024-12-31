// Fill out your copyright notice in the Description page of Project Settings.


#include "Shared/AnimNotify/Psych/ANS_Psych_DumpTruck.h"

#include "Actor/PsychokineticPropBase.h"
#include "Character/Character_Kasane.h"
#include "Components/PsychokinesisComponent.h"
#include "Components/TargetTrackingSpringArmComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

void UANS_Psych_DumpTruck::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                       float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	CurrentFrames = 0;
	if (ACharacter_Kasane* Kasane = Cast<ACharacter_Kasane>(MeshComp->GetOwner()))
	{
		if (Kasane->GetPsychokinesisComponent())
		{
			Truck = Kasane->GetPsychokinesisComponent()->GetCurrentPsychTarget();
		}

		if (Truck && Kasane->GetTargetTrackingComponent())
		{
			FallingLocation = Kasane->GetTargetTrackingComponent()->GetCurrentTarget()->GetActorLocation();
			FallingLocation.Z = Truck->GetActorLocation().Z + 500;
		}
	}
}

void UANS_Psych_DumpTruck::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	CurrentFrames++;
	if (Truck)
	{
		if (CurrentFrames > MovingTotalFrames)
		{
		}
		else
		{
			FVector NewLoc = FMath::VInterpTo(Truck->GetActorLocation(), FallingLocation, FrameDeltaTime, 2.f);
			Truck->SetActorLocation(NewLoc);
		}
	}
}

void UANS_Psych_DumpTruck::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if (Truck)
	{
		if (auto ProjectileMovement = Cast<UProjectileMovementComponent>(Truck->GetComponentByClass(UProjectileMovementComponent::StaticClass())))
		{
			ProjectileMovement->SetUpdatedComponent(Truck->GetRootComponent());
			ProjectileMovement->ProjectileGravityScale = 15.0f;
		}
	}
	
	
}
