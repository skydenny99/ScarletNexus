// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PsychokinesisComponent.generated.h"

class APsychokineticThrowableProp;
class UDataAsset_PsychMontage;

UENUM(BlueprintType)
enum class EPsychType : uint8
{
	LeR,
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
	
	UPROPERTY(EditDefaultsOnly, Category="Psych")
	UDataAsset_PsychMontage* PsychMontageData;
	
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* DetectionBoundary;
	
	UPROPERTY()
	TArray<APsychokineticPropBase*> PsychTargetCandidates;
	UPROPERTY()
	APsychokineticPropBase* PsychTarget;
	UPROPERTY()
	USkeletalMeshComponent* PsychSkeletalMesh;
	

	
	
	float UpdateInterval = 0.2f;
	FTimerHandle UpdateTimer;

	void UpdateNearestPsychTarget();
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void UpdatePsychTargetLocation(APsychokineticThrowableProp* Target);
	
public:
	void InitComponents(USphereComponent* InDetectionBoundary, USkeletalMeshComponent* InSkeletalMesh);
	FOnPsychTargetUpdated OnPsychTargetUpdated;

	UFUNCTION(BlueprintPure)
	FORCEINLINE APsychokineticPropBase* GetPsychTarget() const {return PsychTarget;}

	UFUNCTION(BlueprintCallable)
	void PlayGroundPsychMontage(const EPsychType& PsychType, int32 ComboCount);

	UFUNCTION(BlueprintCallable)
	void PlayAerialPsychMontage(int32 ComboCount);
};
