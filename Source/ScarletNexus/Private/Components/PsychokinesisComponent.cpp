// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PsychokinesisComponent.h"

#include "BaseDebugHelper.h"
#include "Actor/PsychokineticPropBase.h"
#include "Actor/PsychokineticThrowableProp.h"
#include "Character/Character_Kasane.h"
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
	if (PsychTargetCandidates.IsEmpty() || bBlockUpdate) return;
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FVector CharacterLocation = GetOwner()->GetActorLocation();
	FVector CharacterForward = GetOwner()->GetActorForwardVector();
	FVector CameraLocation = CameraManager->GetCameraLocation();
	FVector CameraForward = CameraManager->GetActorForwardVector();

	APsychokineticPropBase* NearestPsychTarget = nullptr;
	float CharacterDotProduct = -1;
	float MinDistanceSquared = std::numeric_limits<float>::infinity();
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

void UPsychokinesisComponent::OnUsePsychProp(APsychokineticPropBase* UsedPsychProp)
{
	if (UsedPsychProp)
	{
		PsychTargetCandidates.Remove(UsedPsychProp);
		bBlockUpdate = false;
		if (UsedPsychProp == PsychTarget)
		{
			PsychTarget = nullptr;
		}
		UpdateNearestPsychTarget();
		//Debug::Print("PsychokinesisComponent::OnUsePsychProp");
	}
}

// Called when the game starts
void UPsychokinesisComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TArray<AActor*> OverlappingActors;
	DetectionBoundary->GetOverlappingActors(OverlappingActors, APsychokineticPropBase::StaticClass());
	for (auto Actor : OverlappingActors)
	{
		APsychokineticPropBase* Temp = Cast<APsychokineticPropBase>(Actor);
		if (Temp == nullptr || Temp->IsUsed()) return;
		PsychTargetCandidates.AddUnique(Temp);
		Temp->OnUsePsychProp.BindUObject(this, &UPsychokinesisComponent::OnUsePsychProp);
	}
	GetWorld()->GetTimerManager().SetTimer(UpdateTimer, this, &UPsychokinesisComponent::UpdateNearestPsychTarget, 0.1f, true);
}

void UPsychokinesisComponent::PlayGroundPsychMontage(const EPsychType& PsychType, int32 ComboCount)
{
	auto GroundMontages = PsychMontageData->ObjectGroundAnimMontages.Find(PsychType);
	PsychSkeletalMesh->GetAnimInstance()->Montage_Play(GroundMontages->AnimMontages[ComboCount]);
}

void UPsychokinesisComponent::PlayAerialPsychMontage(int32 ComboCount)
{
	auto AerialMontage = PsychMontageData->ObjectAerialAnimMontages[ComboCount];
	PsychSkeletalMesh->GetAnimInstance()->Montage_Play(AerialMontage);
}

void UPsychokinesisComponent::GetProperPsychType(int32 ComboCount, EPsychType& PsychType, UAnimMontage*& ChargeMontage,
	UAnimMontage*& AttackMontage)
{
	ACharacter_Kasane* Kasane = Cast<ACharacter_Kasane>(GetOwner());
	FVector PsychDirection = PsychTarget->GetActorLocation() - Kasane->GetActorLocation();
	bool IsRightSide = FVector::DotProduct(PsychDirection, Kasane->GetActorRightVector()) > 0;
	do
	{
		PsychType = static_cast<EPsychType>(UKismetMathLibrary::RandomIntegerInRange(0, 5));
	}
	while (PsychType == LastUsedPsychType);

	LastUsedPsychType = PsychType;
	const FCharacterMontageSet* MontageSet = PsychMontageData->CharacterGroundAnimMontageSets.Find(PsychType);
	ChargeMontage = IsRightSide ? MontageSet->RightChargeAnimMontage : MontageSet->LeftChargeAnimMontage;
	AttackMontage = MontageSet->PsychAttackAnimMontages.AnimMontages[ComboCount];
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
	if (Temp == nullptr || Temp->IsUsed()) return;
	PsychTargetCandidates.AddUnique(Temp);
	Temp->OnUsePsychProp.BindUObject(this, &UPsychokinesisComponent::OnUsePsychProp);
}

void UPsychokinesisComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APsychokineticPropBase* Temp = Cast<APsychokineticPropBase>(OtherActor);
	if (Temp == nullptr) return;
	PsychTargetCandidates.Remove(Temp);
	if (Temp == PsychTarget && bBlockUpdate == false)
	{
		PsychTarget = nullptr;
	}
}


void UPsychokinesisComponent::UpdatePsychTargetLocation(APsychokineticThrowableProp* Target, float DeltaTime)
{
	if (Target->IsAttached()) return;
	FVector DesiredLocation = PsychSkeletalMesh->GetBoneLocation(FName("joint_001"));
	if (FVector::DistSquared(DesiredLocation, Target->GetActorLocation()) < 100.f)
	{
		AttachPsychTargetToBone(Target);
	}
	else
	{
		Target->SetActorLocation(UKismetMathLibrary::VInterpTo(Target->GetActorLocation(), DesiredLocation, DeltaTime, 20.f));
		//Debug::Print(FString::Printf(TEXT("Desired Location X: %f, Y: %f, Z: %f"), DesiredLocation.X, DesiredLocation.Y, DesiredLocation.Z));
	}
}

void UPsychokinesisComponent::AttachPsychTargetToBone(APsychokineticThrowableProp* Target)
{
	if (Target->IsAttached()) return;
	Target->AttachToComponent(PsychSkeletalMesh, FAttachmentTransformRules::KeepWorldTransform, FName("joint_001"));
	Target->Attached();
}
