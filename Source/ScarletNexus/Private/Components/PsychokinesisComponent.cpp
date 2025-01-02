// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PsychokinesisComponent.h"

#include "BaseDebugHelper.h"
#include "Actor/PsychokineticPropBase.h"
#include "Actor/PsychokineticSpecialPropBase.h"
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


void UPsychokinesisComponent::UpdateNearestPsychThrowableTarget()
{
	if (bBlockUpdate) return;
	PsychThrowableTarget = UpdateNearestPsychTarget(PsychThrowableTargetCandidates);
	OnPsychThrowableTargetUpdated.Broadcast(PsychThrowableTarget);
}

void UPsychokinesisComponent::UpdateNearestPsychSpecialTarget()
{
	if (bBlockUpdate) return;
	PsychSpecialTarget = UpdateNearestPsychTarget(PsychSpecialTargetCandidates);
	OnPsychSpecialTargetUpdated.Broadcast(PsychSpecialTarget);
}

APsychokineticPropBase* UPsychokinesisComponent::UpdateNearestPsychTarget(TArray<APsychokineticPropBase*> PropList) const
{
	if (PropList.IsEmpty()) return nullptr;
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FVector CharacterLocation = GetOwner()->GetActorLocation();
	FVector CharacterForward = GetOwner()->GetActorForwardVector();
	FVector CameraLocation = CameraManager->GetCameraLocation();
	FVector CameraForward = CameraManager->GetActorForwardVector();

	APsychokineticPropBase* NearestPsychTarget = nullptr;
	float CharacterDotProduct = -1;
	float MinDistanceSquared = std::numeric_limits<float>::infinity();
	for (auto Candidate : PropList)
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
	return NearestPsychTarget;
}

void UPsychokinesisComponent::OnUsePsychProp(APsychokineticPropBase* UsedPsychProp)
{
	if (APsychokineticThrowableProp* ThrowableProp = Cast<APsychokineticThrowableProp>(UsedPsychProp))
	{
		PsychThrowableTargetCandidates.Remove(ThrowableProp);
		bBlockUpdate = false;
		UpdateNearestPsychThrowableTarget();
		//Debug::Print("PsychokinesisComponent::OnUsePsychProp");
	}
	else if (APsychokineticSpecialPropBase* SpecialProp = Cast<APsychokineticSpecialPropBase>(UsedPsychProp))
	{
		PsychSpecialTargetCandidates.Remove(SpecialProp);
		bBlockUpdate = false;
		UpdateNearestPsychSpecialTarget();
		//Debug::Print("PsychokinesisComponent::OnUsePsychProp");
	}
	
	if (UsedPsychProp == CurrentPsychTarget)
	{
		CurrentPsychTarget = nullptr;
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
		if (Cast<APsychokineticThrowableProp>(Temp))
		{
			PsychThrowableTargetCandidates.AddUnique(Temp);
		}
		else
		{
			PsychSpecialTargetCandidates.AddUnique(Temp);
		}
		Temp->OnUsePsychProp.BindUObject(this, &UPsychokinesisComponent::OnUsePsychProp);
	}
	GetWorld()->GetTimerManager().SetTimer(ThrowableUpdateTimer, this, &UPsychokinesisComponent::UpdateNearestPsychThrowableTarget, 0.1f, true);
	GetWorld()->GetTimerManager().SetTimer(SpecialUpdateTimer, this, &UPsychokinesisComponent::UpdateNearestPsychSpecialTarget, 0.1f, true);
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

void UPsychokinesisComponent::PlayJustDodgePsychMontage()
{
	PsychSkeletalMesh->GetAnimInstance()->Montage_Play(PsychMontageData->ObjectJustDodgeMontage);
}

void UPsychokinesisComponent::CancelPlayingPsychMontage()
{
	if (APsychokineticThrowableProp* ThrowableProp = Cast<APsychokineticThrowableProp>(CurrentPsychTarget))
	{
		ThrowableProp->OnPsychAttackCancel();
	}
	PsychSkeletalMesh->GetAnimInstance()->StopAllMontages(0.f);
	
}

void UPsychokinesisComponent::GetProperPsychType(int32 ComboCount, EPsychType& PsychType, UAnimMontage*& ChargeMontage,
                                                 UAnimMontage*& AttackMontage)
{
	ACharacter_Kasane* Kasane = Cast<ACharacter_Kasane>(GetOwner());
	FVector PsychDirection = CurrentPsychTarget->GetActorLocation() - Kasane->GetActorLocation();
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
	if (Cast<APsychokineticThrowableProp>(Temp))
	{
		PsychThrowableTargetCandidates.AddUnique(Temp);
	}
	else
	{
		PsychSpecialTargetCandidates.AddUnique(Temp);
	}
	Temp->OnUsePsychProp.BindUObject(this, &UPsychokinesisComponent::OnUsePsychProp);
}

void UPsychokinesisComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APsychokineticPropBase* Temp = Cast<APsychokineticPropBase>(OtherActor);
	if (Temp == nullptr) return;
	if (Cast<APsychokineticThrowableProp>(Temp))
	{
		PsychThrowableTargetCandidates.Remove(Temp);
		if (Temp == PsychThrowableTarget && bBlockUpdate == false)
		{
			PsychThrowableTarget = nullptr;
			OnPsychThrowableTargetUpdated.Broadcast(PsychThrowableTarget);
		}
	}
	else
	{
		PsychSpecialTargetCandidates.Remove(Temp);
		if (Temp == PsychSpecialTarget && bBlockUpdate == false)
		{
			PsychSpecialTarget = nullptr;
			OnPsychSpecialTargetUpdated.Broadcast(PsychSpecialTarget);
		}
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

void UPsychokinesisComponent::OverrideSpecialTarget(AActor* InActor)
{
	APsychokineticPropBase* Temp = Cast<APsychokineticSpecialPropBase>(InActor);
	if (Temp == nullptr) return;
	Temp->OnUsePsychProp.BindUObject(this, &UPsychokinesisComponent::OnUsePsychProp);
	PsychSpecialTarget = Temp;
	OnPsychSpecialTargetUpdated.Broadcast(PsychSpecialTarget);
}

void UPsychokinesisComponent::OverrideThrowableTarget(AActor* InActor)
{
	APsychokineticPropBase* Temp = Cast<APsychokineticThrowableProp>(InActor);
	if (Temp == nullptr) return;
	Temp->OnUsePsychProp.BindUObject(this, &UPsychokinesisComponent::OnUsePsychProp);
	PsychThrowableTarget = Temp;
	OnPsychThrowableTargetUpdated.Broadcast(PsychThrowableTarget);
}
