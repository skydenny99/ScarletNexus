// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TargetTrackingSpringArmComponent.h"

#include "BaseDebugHelper.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


void UTargetTrackingSpringArmComponent::SortByDistance()
{
	if (FoundTargets.IsEmpty()) return;
	FoundTargets.Sort([this] (const AActor& left, const AActor& right)
	{
		AActor* Owner = this->GetOwner();
		return FVector::DistSquared2D(Owner->GetActorLocation(), left.GetActorLocation())
		< FVector::DistSquared2D(Owner->GetActorLocation(), right.GetActorLocation());
	});
	TargetIndex = 0;
}

void UTargetTrackingSpringArmComponent::ChangeTarget(bool bIsLeft)
{
	if (FoundTargets.IsEmpty()) return;
	TargetIndex = (TargetIndex + (bIsLeft ? -1 : 1) + FoundTargets.Num()) % FoundTargets.Num();
	TargetActor = FoundTargets[TargetIndex];
	OnTargetUpdated.ExecuteIfBound(TargetActor);
}

void UTargetTrackingSpringArmComponent::ToggleTargetTracking()
{
	SetTargetTracking(!bIsTargetTracking);
}

void UTargetTrackingSpringArmComponent::SetTargetTracking(bool IsTargetTracking)
{
	bIsTargetTracking = IsTargetTracking && (FoundTargets.IsEmpty() == false);
	if (bIsTargetTracking)
	{
		SortByDistance();
		TargetIndex = 0;
		TargetActor = FoundTargets[TargetIndex];
		OnTargetUpdated.ExecuteIfBound(TargetActor);
	}
	else
	{
		TargetActor = nullptr;
	}
}

FRotator UTargetTrackingSpringArmComponent::GetDesiredRotation() const
{
	FRotator DesiredRot = GetComponentRotation();
	APawn* OwningPawn = Cast<APawn>(GetOwner());
	if (OwningPawn == nullptr)
		return DesiredRot;
	
	const FRotator PawnViewRotation = OwningPawn->GetViewRotation();
	if (DesiredRot != PawnViewRotation)
	{
		DesiredRot = PawnViewRotation;
	}
	
	if (bOverrideTrackingTarget)
	{
		if (OverrideTargetActor == nullptr)
			return DesiredRot;
	}
	else
	{
		if (bUpdateCameraTracking == false)
			return DesiredRot;
		if (TargetActor == nullptr)
			return DesiredRot;
	}
	
	const AActor* Target = bOverrideTrackingTarget ? OverrideTargetActor : TargetActor;
	const auto [BoundaryLeft, BoundaryRight, BoundaryTop, BoundaryBottom]
	= bOverrideTrackingTarget ? OverrideTrackingBoundary : DefaultTrackingBoundary;
	
	const FVector TargetLocation = Target->GetActorLocation();
	FRotator TargetLookRotator = UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(), TargetLocation);
	TargetLookRotator.Roll = DesiredRot.Roll;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (bFixedTrackingTarget)
	{
		PlayerController->SetControlRotation(TargetLookRotator);
		return TargetLookRotator;
	}
	
	FVector2D TargetScreenLocation = FVector2D::ZeroVector;
	const bool bProjectResult = PlayerController->ProjectWorldLocationToScreen(TargetLocation, TargetScreenLocation);
	int32 ScreenWidth = 0, ScreenHeight = 0;
	PlayerController->GetViewportSize(ScreenWidth, ScreenHeight);
	TargetScreenLocation.X /= ScreenWidth;
	TargetScreenLocation.Y /= ScreenHeight;

	if (bProjectResult == false || TargetScreenLocation.X < BoundaryLeft  || TargetScreenLocation.X > 1 - BoundaryRight
		|| TargetScreenLocation.Y < BoundaryTop  || TargetScreenLocation.Y > 1 - BoundaryBottom)
	{
		TargetLookRotator = FMath::RInterpTo(DesiredRot, TargetLookRotator, GetWorld()->GetDeltaSeconds(), 8.0f);
		PlayerController->SetControlRotation(TargetLookRotator);
		return TargetLookRotator;
	}
	return DesiredRot;
}

void UTargetTrackingSpringArmComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bOverrideTrackingTarget || bFixedTrackingTarget)
	{
		bUpdateCameraTracking = true;
	}
	else
	{
		if (ResetTimer > ResetThreshold)
		{
			bUpdateCameraTracking = bIsTargetTracking;
		}
		else
		{
			bUpdateCameraTracking = false;
			ResetTimer += DeltaTime;
		}
	}
	
}

AActor* UTargetTrackingSpringArmComponent::GetCurrentTarget()
{
	if (TargetActor)
		return TargetActor;
	SortByDistance();
	return FoundTargets.IsEmpty() ? nullptr : FoundTargets[0];
}

void UTargetTrackingSpringArmComponent::OnEnemyDead(AActor* InTargetActor)
{
	if (InTargetActor == TargetActor)
	{
		TargetActor = nullptr;
	}
	FoundTargets.Remove(InTargetActor);
	if (TargetIndex >= FoundTargets.Num())
	{
		TargetIndex = 0;
	}
	
	if (FoundTargets.IsEmpty() == false)
	{
		TargetActor = FoundTargets[TargetIndex];
	}
	else
	{
		TargetActor = nullptr;
	}
	
	OnTargetUpdated.ExecuteIfBound(TargetActor);
}

void UTargetTrackingSpringArmComponent::SetCurrentTrackingTarget(AActor* InTargetActor)
{
	TargetActor = InTargetActor;
	if (FoundTargets.Contains(TargetActor))
	{
		TargetIndex = FoundTargets.Find(TargetActor);
	}
	OnTargetUpdated.ExecuteIfBound(TargetActor);
}