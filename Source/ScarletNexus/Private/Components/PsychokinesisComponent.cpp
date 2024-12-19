// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PsychokinesisComponent.h"

#include "BaseDebugHelper.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPsychokinesisComponent::UPsychokinesisComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


void UPsychokinesisComponent::UpdateNearestPsychTarget()
{
	if (PsychTargetCandidates.IsEmpty()) return;
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FVector CharacterLocation = GetOwner()->GetActorLocation();
	FVector CharacterForward = GetOwner()->GetActorForwardVector();
	FVector CameraLocation = CameraManager->GetCameraLocation();
	FVector CameraForward = CameraManager->GetActorForwardVector();

	AActor* NearestPsychTarget = nullptr;
	float CharacterDotProduct = -1;
	float MinDistanceSquared = INFINITY;
	for (auto Candidate : PsychTargetCandidates)
	{
		if (Candidate->IsValidLowLevel() == false) continue;
		FVector CharacterTargetDistance = Candidate->GetActorLocation() - CharacterLocation;
		float TempCharacterDot = FVector::DotProduct(CharacterTargetDistance.GetSafeNormal(), CharacterForward);
		if (TempCharacterDot <= 0)
		{
			if (CharacterDotProduct <= 0)
			{
				float DistanceSquared = CharacterTargetDistance.SquaredLength();
				if (MinDistanceSquared > DistanceSquared)
				{
					CharacterDotProduct = TempCharacterDot;
					MinDistanceSquared = DistanceSquared;
					NearestPsychTarget = Candidate;
				}
			}
		}
		else
		{
			float DistanceSquared = FMath::Abs(1 - FVector::DotProduct((Candidate->GetActorLocation() - CameraLocation).GetSafeNormal(), CameraForward))
									* CharacterTargetDistance.SquaredLength();
			if (CharacterDotProduct <= 0 || MinDistanceSquared > DistanceSquared)
			{
				CharacterDotProduct = TempCharacterDot;
				MinDistanceSquared = DistanceSquared;
				NearestPsychTarget = Candidate;
			}
		}
		
	}
	PsychTarget = NearestPsychTarget;
	OnPsychTargetUpdated.Broadcast(PsychTarget);
}

// Called when the game starts
void UPsychokinesisComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GetWorld()->GetTimerManager().SetTimer(UpdateTimer, this, &UPsychokinesisComponent::UpdateNearestPsychTarget, 0.1f, true);
}

void UPsychokinesisComponent::InitBoundary(USphereComponent* InDetectionBoundary)
{
	check(InDetectionBoundary);
	DetectionBoundary = InDetectionBoundary;
	DetectionBoundary->OnComponentBeginOverlap.AddDynamic(this, &UPsychokinesisComponent::OnOverlapBegin);
	DetectionBoundary->OnComponentEndOverlap.AddDynamic(this, &UPsychokinesisComponent::OnOverlapEnd);
}


void UPsychokinesisComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) return;
	PsychTargetCandidates.AddUnique(OtherActor);
}

void UPsychokinesisComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PsychTargetCandidates.Remove(OtherActor);
}
