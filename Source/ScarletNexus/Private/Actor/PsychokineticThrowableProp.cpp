// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PsychokineticThrowableProp.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AIController.h"
#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
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

void APsychokineticThrowableProp::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent->OnComponentHit.AddDynamic(this, &APsychokineticThrowableProp::OnMeshHit);
}


void APsychokineticThrowableProp::OnStartGrab()
{
	MeshComponent->SetCollisionProfileName("PlayerProjectile");
}

void APsychokineticThrowableProp::OnHit()
{
	ProjectileMovementComponent->ProjectileGravityScale = 1.f;
	MeshComponent->SetCollisionProfileName("EndProjectile");
	SetLifeSpan(1.f);
}

void APsychokineticThrowableProp::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = OtherActor;
	
	// Hit.GetComponent()->Get
	switch (Hit.Component->GetCollisionObjectType())
	{
	case ECC_GameTraceChannel3:
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, BaseGameplayTags::Shared_Event_HitReact_KnockDown, Data);
			Debug::Print(TEXT("Hit!!!!!!!!!!!"));
			OnHit();
		
		break;
		
	default:
		break;
	}
}

void APsychokineticThrowableProp::OnChargingCancel()
{
	CurrentTargetLocation.Reset();
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
	if (CurrentTargetLocation.IsSet())
	{
		TargetLocation = CurrentTargetLocation.GetValue();
	}
	else if (CurrentTarget != nullptr)
	{
		// TargetLocation = CurrentTarget->GetActorLocation();
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
	// Debug::Print(FString::Printf(TEXT("TargetLocation, %f, %f ,%f"), TargetLocation.X, TargetLocation.Y, TargetLocation.Z ));

	

	
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->Velocity = (GetActorForwardVector() * ProjectileMovementComponent->MaxSpeed);
	SetLifeSpan(5.f);
	bIsUsed = true;
	OnUsePsychProp.ExecuteIfBound(this);
}


