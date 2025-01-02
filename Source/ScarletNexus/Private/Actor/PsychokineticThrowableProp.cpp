// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PsychokineticThrowableProp.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AIController.h"
#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "Actor/GE_Prop.h"
#include "Character/Character_Kasane.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/UI/PropUIComponent.h"
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

	CollisionBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBoxComponent"));
	SetRootComponent(CollisionBoxComponent);
	CollisionBoxComponent->SetCollisionProfileName("BlockAllDynamic");

	InterectComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InterectComponent"));
	InterectComponent->SetupAttachment(MeshComponent);
	
	Damage = 10;
}

void APsychokineticThrowableProp::BeginPlay()
{
	Super::BeginPlay();
	CollisionBoxComponent->OnComponentHit.AddDynamic(this, &APsychokineticThrowableProp::OnMeshHit);
}


void APsychokineticThrowableProp::HandleApplyProp(APawn* HitPawn, FGameplayEventData& Payload)
{
	
	// ACharacter_Kasane* Player = Cast<ACharacter_Kasane>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	 const bool bWasApplied = UBaseFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(PropDamageSpecHandle.Data->GetContext().GetInstigator(), HitPawn, PropDamageSpecHandle);
	if (bWasApplied)
	 {
	 	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
	 		HitPawn,
	 		BaseGameplayTags::Shared_Event_HitReact_KnockDown,
	 		Payload
	 	);
	 }

	
}

void APsychokineticThrowableProp::OnStartGrab(bool NeedToClone, bool DoubleClone)
{
	ProjectileMovementComponent->SetUpdatedComponent(nullptr);
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;
	CollisionBoxComponent->SetCollisionProfileName("PlayerProjectile");
	CachedLaunchedLocation = GetActorLocation();
	CachedLaunchedRotation = GetActorRotation();
	bIsUsed = true;
	// if SAS: clone activated - Launch Clone
	if (bCanClonable && NeedToClone)
	{
		FTimerHandle TempTimerHandle;
		GetWorldTimerManager().SetTimer(TempTimerHandle, this, &APsychokineticThrowableProp::CloneLaunch, 0.5f);
		if (DoubleClone)
		{
			FTimerHandle TempTimerHandle2;
			GetWorldTimerManager().SetTimer(TempTimerHandle2, this, &APsychokineticThrowableProp::CloneLaunch, 0.8f);
		}
		
	}
}

void APsychokineticThrowableProp::OnHit()
{
	ProjectileMovementComponent->ProjectileGravityScale = 1.f;
	CollisionBoxComponent->SetCollisionProfileName("EndProjectile");
	SetLifeSpan(1.f);
}

void APsychokineticThrowableProp::OnMeshHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = OtherActor;
	APawn* HitPawn = Cast<APawn>(OtherActor);
	// Hit.GetComponent()->Get
	switch (Hit.Component->GetCollisionObjectType())
	{
	case ECC_GameTraceChannel3:
			// UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, BaseGameplayTags::Shared_Event_HitReact_KnockDown, Data);
			// UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, BaseGameplayTags::Shared_Event_HitReact_Critical, Data);
			//Debug::Print(TEXT("Hit!!!!!!!!!!!"));

			HandleApplyProp(HitPawn, Data);
			Debug::Print(FString::Printf(TEXT("HitPawn: %s"), *HitPawn->GetName()));
			Debug::Print(FString::Printf(TEXT("Instigator: %s"), *Data.Instigator.GetName()));
		
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

void APsychokineticThrowableProp::OnPsychAttackCancel()
{
	//MeshComponent->SetSimulatePhysics(true);
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->Velocity = (GetActorForwardVector() * 500.f);
	OnHit();
}

void APsychokineticThrowableProp::FloatingTick(float DeltaTime)
{
	SetActorLocation(UKismetMathLibrary::VInterpTo(GetActorLocation(), GetActorLocation() + FVector::UpVector * (FloatingHeight / ChargeTime), DeltaTime, 1.f));
}

void APsychokineticThrowableProp::Launch()
{
	CollisionBoxComponent->SetCollisionProfileName("PlayerProjectile");
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
	// Debug::Print(FString::Printf(TEXT("TargetLocation, %f, %f ,%f"), TargetLocation.X, TargetLocation.Y, TargetLocation.Z ));

	

	
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
	ProjectileMovementComponent->Velocity = (GetActorForwardVector() * ProjectileMovementComponent->MaxSpeed);
	SetLifeSpan(5.f);
	OnUsePsychProp.ExecuteIfBound(this);
}

void APsychokineticThrowableProp::CloneLaunch()
{
	if (IsValidChecked(this) == false) return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Template = this;
	APsychokineticThrowableProp* ClonedProp = GetWorld()->SpawnActor<APsychokineticThrowableProp>(GetClass(), SpawnParams);
	ClonedProp->SetActorLocation(CachedLaunchedLocation);
	ClonedProp->SetActorRotation(CachedLaunchedRotation);
	ClonedProp->bIsAttached = true;
	ClonedProp->bCanClonable = false;
	if (CurrentTargetLocation.IsSet())
	{
		ClonedProp->SetTarget(CurrentTargetLocation.GetValue());
	}
	else if (CurrentTarget != nullptr)
	{
		ClonedProp->SetTarget(CurrentTarget);
	}
	ClonedProp->Launch();
}


