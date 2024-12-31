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
	
	FVector TargetLocation = Target->GetActorLocation();
	FVector2D TargetScreenLocation = FVector2D::ZeroVector;
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	bool bProjectResult = PlayerController->ProjectWorldLocationToScreen(TargetLocation, TargetScreenLocation);
	int32 ScreenWidth = 0, ScreenHeight = 0;
	PlayerController->GetViewportSize(ScreenWidth, ScreenHeight);
	TargetScreenLocation.X /= ScreenWidth;
	TargetScreenLocation.Y /= ScreenHeight;
	// if (bProjectResult == false)
	// 	return DesiredRot;
	
	// float LeftBoundary = GSystemResolution.ResX * BoundaryLeft;
	// float RightBoundary = GSystemResolution.ResX * (1 - BoundaryRight);
	// float TopBoundary = GSystemResolution.ResY * BoundaryTop;
	// float BottomBoundary = GSystemResolution.ResY * (1 + BoundaryBottom);

	if (bProjectResult == false || TargetScreenLocation.X < BoundaryLeft  || TargetScreenLocation.X > 1 - BoundaryRight
		|| TargetScreenLocation.Y < BoundaryTop  || TargetScreenLocation.Y > 1 - BoundaryBottom)
	{
		FRotator TargetLookRotator = UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(), TargetLocation);
		TargetLookRotator.Roll = DesiredRot.Roll;
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
	if (bOverrideTrackingTarget)
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
	if (FoundTargets.IsEmpty())
		return nullptr;
	if (TargetActor)
		return TargetActor;
	SortByDistance();
	
	return FoundTargets.IsEmpty() ? nullptr : FoundTargets[0];
}
