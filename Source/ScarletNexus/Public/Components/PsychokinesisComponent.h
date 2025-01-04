// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseDebugHelper.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PsychokinesisComponent.generated.h"

class APsychokineticSpecialPropBase;
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
DECLARE_DELEGATE_TwoParams(FOnPsychPropChangedDelegate, APsychokineticPropBase*, bool);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCARLETNEXUS_API UPsychokinesisComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPsychokinesisComponent();

protected:
	FOnPsychPropChangedDelegate OnPsychThrowableTargetUpdated;
	FOnPsychPropChangedDelegate OnPsychSpecialTargetUpdated;
	
	bool bBlockUpdate = false;
	
	UPROPERTY(EditDefaultsOnly, Category="Psych")
	UDataAsset_PsychMontage* PsychMontageData;
	
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* DetectionBoundary;
	
	UPROPERTY()
	TArray<APsychokineticPropBase*> PsychThrowableTargetCandidates;
	TArray<APsychokineticPropBase*> PsychSpecialTargetCandidates;
	UPROPERTY()
	APsychokineticPropBase* PsychThrowableTarget;
	UPROPERTY()
	APsychokineticPropBase* PsychSpecialTarget;
	UPROPERTY()
	APsychokineticPropBase* CurrentPsychTarget;
	
	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* PsychSkeletalMesh;

	EPsychType LastUsedPsychType = EPsychType::AeR;
	
	
	float UpdateInterval = 0.2f;
	FTimerHandle ThrowableUpdateTimer;
	FTimerHandle SpecialUpdateTimer;

	void UpdateNearestPsychThrowableTarget();
	void UpdateNearestPsychSpecialTarget();
	APsychokineticPropBase* UpdateNearestPsychTarget(TArray<APsychokineticPropBase*> PropList) const;
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

	UFUNCTION(BlueprintCallable)
	void OverrideSpecialTarget(AActor* InActor);
	void OverrideThrowableTarget(AActor* InActor);

	FORCEINLINE APsychokineticPropBase* GetPsychThrowableTarget() const {return PsychThrowableTarget;}
	FORCEINLINE APsychokineticPropBase* GetPsychSpecialTarget() const {return PsychSpecialTarget;}
	FORCEINLINE void SetCurrentPsychTarget(APsychokineticPropBase* PsychTarget) {  CurrentPsychTarget = PsychTarget; }
	FORCEINLINE APsychokineticPropBase* GetCurrentPsychTarget() const { return CurrentPsychTarget; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetBlockUpdate(bool InBlockUpdate)
	{
		//Debug::Print(FString::Printf(TEXT("PsychokinesisComponent::SetBlockUpdate - %s"), *FString(InBlockUpdate ? "Block" : "Release")));
		bBlockUpdate = InBlockUpdate;
	}

	UFUNCTION(BlueprintCallable)
	void PlayGroundPsychMontage(const EPsychType& PsychType, int32 ComboCount);

	UFUNCTION(BlueprintCallable)
	void PlayAerialPsychMontage(int32 ComboCount);

	UFUNCTION(BlueprintCallable)
	void PlayJustDodgePsychMontage();

	UFUNCTION(BlueprintCallable)
	void CancelPlayingPsychMontage();

	USkeletalMeshComponent* GetPsychSkeletalMesh() const { return PsychSkeletalMesh; }
	

	UFUNCTION(BlueprintCallable, Category = "Psych")
	void GetProperPsychType(int32 ComboCount, EPsychType& PsychType, UAnimMontage*& ChargeMontage, UAnimMontage*& AttackMontage);
	
};
