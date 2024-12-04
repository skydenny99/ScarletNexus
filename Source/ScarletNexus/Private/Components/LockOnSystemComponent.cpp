// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/LockOnSystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"

struct FActorDistanceCompare
{
	AActor* Owner;
	FORCEINLINE bool operator()(const AActor& A,const AActor& B) const 
	{ 
		return FVector::DistSquared2D(Owner->GetActorLocation(), A.GetActorLocation())
			< FVector::DistSquared2D(Owner->GetActorLocation(), B.GetActorLocation());
	}
};

// Sets default values for this component's properties
ULockOnSystemComponent::ULockOnSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	ObjectQueries.AddUnique(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	IgnoreActors.AddUnique(GetOwner());
}


// Called when the game starts
void ULockOnSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void ULockOnSystemComponent::OnAttackTarget(AActor* Target)
{
	if (CurrentTarget) return;
	GetNearestTarget();
	if (Target != CurrentTarget)
	{
		TargetList.RemoveSingle(Target);
		TargetList.Insert(Target, 0);
		CurrentTarget = Target;
		CurrentTargetIndex = 0;
	}
	OnChangeTarget.Broadcast(CurrentTarget);
}

void ULockOnSystemComponent::OnTargetDeath(AActor* Target)
{
	TargetList.RemoveSingle(Target);
	CurrentTarget = nullptr;
	if (TargetList.IsEmpty() == false)
	{
		CurrentTargetIndex = CurrentTargetIndex % TargetList.Num();
		CurrentTarget = TargetList[CurrentTargetIndex];
	}
	OnChangeTarget.Broadcast(CurrentTarget);
}

AActor* ULockOnSystemComponent::GetNearestTarget()
{
	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		GetOwner()->GetActorLocation(),
		5000.f, 
		ObjectQueries,
		AActor::StaticClass(),
		IgnoreActors,
		TargetList
	);

	if (TargetList.IsEmpty()) return nullptr;

	FActorDistanceCompare Compare{ GetOwner()};
	TargetList.HeapSort(Compare);
	CurrentTarget = TargetList[0];
	CurrentTargetIndex = 0;
	return CurrentTarget;
}

AActor* ULockOnSystemComponent::SwitchTarget(bool bLeft)
{
	if (TargetList.IsEmpty()) return nullptr;
	int32 increFactor = bLeft ? -1 : 1;
	CurrentTargetIndex = (CurrentTargetIndex + increFactor + TargetList.Num()) % TargetList.Num();
	CurrentTarget = TargetList[CurrentTargetIndex];
	return CurrentTarget;
}

