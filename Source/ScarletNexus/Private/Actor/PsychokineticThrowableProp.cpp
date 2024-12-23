// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PsychokineticThrowableProp.h"

#include "BaseDebugHelper.h"
#include "GameFramework/ProjectileMovementComponent.h"
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



void APsychokineticThrowableProp::Launch()
{
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	SetActorLocation(GetActorLocation() + FVector(0, 0, 300));
	if (TargetActor)
	{
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetActor->GetActorLocation());
		SetActorRotation(LookAtRot);
	}
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->Velocity = (GetActorForwardVector() * 5000.f); 
}


