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
	ProjectileMovementComponent->MaxSpeed = 7000.f;
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
}


void APsychokineticThrowableProp::OnStartGrab()
{
	MeshComponent->SetCollisionProfileName("PlayerProjectile");
}

void APsychokineticThrowableProp::OnHit()
{
	ProjectileMovementComponent->ProjectileGravityScale = 2.f;
	MeshComponent->SetCollisionProfileName("EndProjectile");
	SetLifeSpan(2.f);
}

void APsychokineticThrowableProp::OnChargingCancel()
{
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	CurrentControlNum++;
	if (CurrentControlNum >= MaxControlNum)
	{
		OnHit();
	}
}

void APsychokineticThrowableProp::FloatingTick(float DeltaTime)
{
	SetActorLocation(UKismetMathLibrary::VInterpTo(GetActorLocation(), GetActorLocation() + FVector::UpVector * (FloatingHeight / ChargeTime), DeltaTime, 1.f));
}

void APsychokineticThrowableProp::Launch()
{
	MeshComponent->SetCollisionProfileName("PlayerProjectile");
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
	ProjectileMovementComponent->Velocity = (GetActorForwardVector() * ProjectileMovementComponent->MaxSpeed);
	SetLifeSpan(5.f);
	bIsUsed = true;
	OnUsePsychProp.ExecuteIfBound(this);
}


