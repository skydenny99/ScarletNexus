// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PsychokinesisComponent.h"

#include "BaseDebugHelper.h"
#include "Actor/PsychokineticPropBase.h"
#include "Actor/PsychokineticThrowableProp.h"
#include "Components/SphereComponent.h"
#include "DataAsset/DataAsset_PsychMontage.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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

	APsychokineticPropBase* NearestPsychTarget = nullptr;
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

void UPsychokinesisComponent::PlayGroundPsychMontage(const EPsychType& PsychType, int32 ComboCount)
{
	auto GroundMontages = PsychMontageData->GroundAnimMontages.Find(PsychType);
	PsychSkeletalMesh->GetAnimInstance()->Montage_Play(GroundMontages->AnimMontages[ComboCount]);
}

void UPsychokinesisComponent::PlayAerialPsychMontage(int32 ComboCount)
{
}


void UPsychokinesisComponent::InitComponents(USphereComponent* InDetectionBoundary,
											 USkeletalMeshComponent* InSkeletalMesh)
{
	check(InDetectionBoundary);
	DetectionBoundary = InDetectionBoundary;
	DetectionBoundary->OnComponentBeginOverlap.AddDynamic(this, &UPsychokinesisComponent::OnOverlapBegin);
	DetectionBoundary->OnComponentEndOverlap.AddDynamic(this, &UPsychokinesisComponent::OnOverlapEnd);

	check(InSkeletalMesh)
	PsychSkeletalMesh = InSkeletalMesh;
}

void UPsychokinesisComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APsychokineticPropBase* Temp = Cast<APsychokineticPropBase>(OtherActor);
	if (Temp == nullptr) return;
	PsychTargetCandidates.AddUnique(Temp);
}

void UPsychokinesisComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APsychokineticPropBase* Temp = Cast<APsychokineticPropBase>(OtherActor);
	if (Temp == nullptr) return;
	PsychTargetCandidates.Remove(Temp);
	if (Temp == PsychTarget)
	{
		PsychTarget = nullptr;
	}
}


void UPsychokinesisComponent::UpdatePsychTargetLocation(APsychokineticThrowableProp* Target)
{
	if (Target->IsAttached()) return;
	FVector DesiredLocation = PsychSkeletalMesh->GetBoneLocation(FName("joint_001"));
	if (FVector::Distance(DesiredLocation, Target->GetActorLocation()) < 100.f)
	{
		Target->AttachToComponent(PsychSkeletalMesh, FAttachmentTransformRules::KeepWorldTransform, FName("joint_001"));
		Target->Attached();
	}
	else
	{
		Target->SetActorLocation(UKismetMathLibrary::VInterpTo(Target->GetActorLocation(), DesiredLocation, GetWorld()->GetDeltaSeconds(), 15.f));
	}
}
