// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PsychokineticThrowableProp.h"

#include "BaseDebugHelper.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APsychokineticThrowableProp::APsychokineticThrowableProp()
{
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 0.f;
	ProjectileMovementComponent->MaxSpeed = 10000.f;
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
}


void APsychokineticThrowableProp::FloatingTick(float DeltaTime)
{
	SetActorLocation(UKismetMathLibrary::VInterpTo(GetActorLocation(), GetActorLocation() + FVector::UpVector * (FloatingHeight / ChargeTime), DeltaTime, 1.f));
}

void APsychokineticThrowableProp::Launch()
{
	if (bIsAttached)
	{
		DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	FVector TargetLocation = FVector::ZeroVector;
	if (CurrentTarget != nullptr)
	{
		TargetLocation = CurrentTarget->GetActorLocation();
	}
	else
	{
		if (APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0))
		{
			TargetLocation = CameraManager->GetActorForwardVector() * 1000.f;
		}
	}
	const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
	SetActorRotation(LookAtRot);
	
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->Velocity = (GetActorForwardVector() * 5000.f);
	SetLifeSpan(5.f);
}


