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
	}
	else
	{
		TargetActor = nullptr;
	}
}

void UTargetTrackingSpringArmComponent::SetTargetTrackingByAttack(AActor* AttackTarget)
{
	TargetActor = AttackTarget;
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
	
	if (bUpdateCameraTracking == false || TargetActor == nullptr)
		return DesiredRot;
	
	FVector TargetLocation = TargetActor->GetActorLocation();
	FVector2D TargetScreenLocation = FVector2D::ZeroVector;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool bProjectResult = PlayerController->ProjectWorldLocationToScreen(TargetLocation, TargetScreenLocation);
	// if (bProjectResult == false)
	// 	return DesiredRot;
	float LeftBoundary = GSystemResolution.ResX * TrackingBoundary.BoundaryLeft;
	float RightBoundary = GSystemResolution.ResX * (1 - TrackingBoundary.BoundaryRight);
	float TopBoundary = GSystemResolution.ResY * TrackingBoundary.BoundaryTop;
	float BottomBoundary = GSystemResolution.ResY * (1 - TrackingBoundary.BoundaryBottom);
	
	if (bProjectResult == false || TargetScreenLocation.X < LeftBoundary  || TargetScreenLocation.X > RightBoundary
		|| TargetScreenLocation.Y < TopBoundary  || TargetScreenLocation.Y > BottomBoundary)
	{
		FRotator TargetLookRotator = UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(), TargetLocation);
		TargetLookRotator.Roll = DesiredRot.Roll;
		TargetLookRotator = FMath::RInterpTo(DesiredRot, TargetLookRotator, GetWorld()->GetDeltaSeconds(), 3.0f);
		PlayerController->SetControlRotation(TargetLookRotator);
		return TargetLookRotator;
	}
	return DesiredRot;
}

void UTargetTrackingSpringArmComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
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
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AActor* UTargetTrackingSpringArmComponent::GetCurrentTarget()
{
	if (FoundTargets.IsEmpty())
		return nullptr;
	if (TargetActor)
		return TargetActor;
	SortByDistance();
	
	return FoundTargets.IsEmpty() ? nullptr : FoundTargets[0];
}
