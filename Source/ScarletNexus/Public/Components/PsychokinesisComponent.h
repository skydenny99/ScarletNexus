// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDebugHelper.h"
#include "Components/ActorComponent.h"
#include "PsychokinesisComponent.generated.h"

class APsychokineticThrowableProp;
class UDataAsset_PsychMontage;

UENUM(BlueprintType)
enum class EPsychType : uint8
{
	LeR = 0,
	LeL,
	AeL,
	AeR,
	ReR,
	ReL
};

class APsychokineticPropBase;
class USphereComponent;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPsychTargetUpdated, APsychokineticPropBase*)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCARLETNEXUS_API UPsychokinesisComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPsychokinesisComponent();

protected:
	bool bBlockUpdate = false;
	
	UPROPERTY(EditDefaultsOnly, Category="Psych")
	UDataAsset_PsychMontage* PsychMontageData;
	
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* DetectionBoundary;
	
	UPROPERTY()
	TArray<APsychokineticPropBase*> PsychTargetCandidates;
	UPROPERTY()
	APsychokineticPropBase* PsychTarget;
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* PsychSkeletalMesh;

	EPsychType LastUsedPsychType = EPsychType::AeR;
	
	
	float UpdateInterval = 0.2f;
	FTimerHandle UpdateTimer;

	void UpdateNearestPsychTarget();
	void OnUsePsychProp(APsychokineticPropBase* UsedPsychProp);
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
public:
	void InitComponents(USphereComponent* InDetectionBoundary, USkeletalMeshComponent* InSkeletalMesh);
	void UpdatePsychTargetLocation(APsychokineticThrowableProp* Target, float DeltaTime);
	void AttachPsychTargetToBone(APsychokineticThrowableProp* Target);
	FOnPsychTargetUpdated OnPsychTargetUpdated;

	void SetPsychTargetInForce(AActor* InActor);

	UFUNCTION(BlueprintPure)
	APsychokineticPropBase* GetPsychTarget() const {return PsychTarget;}

	FORCEINLINE void SetBlockUpdate(bool InBlockUpdate)
	{
		Debug::Print(FString::Printf(TEXT("PsychokinesisComponent::SetBlockUpdate - %s"), *FString(InBlockUpdate ? "Block" : "Release")));
		bBlockUpdate = InBlockUpdate;
	}

	UFUNCTION(BlueprintCallable)
	void PlayGroundPsychMontage(const EPsychType& PsychType, int32 ComboCount);

	UFUNCTION(BlueprintCallable)
	void PlayAerialPsychMontage(int32 ComboCount);

	UFUNCTION(BlueprintCallable)
	void PlayJustDodgePsychMontage();

	USkeletalMeshComponent* GetPsychSkeletalMesh() const { return PsychSkeletalMesh; }
	

	UFUNCTION(BlueprintCallable, Category = "Psych")
	void GetProperPsychType(int32 ComboCount, EPsychType& PsychType, UAnimMontage*& ChargeMontage, UAnimMontage*& AttackMontage);
	
};
