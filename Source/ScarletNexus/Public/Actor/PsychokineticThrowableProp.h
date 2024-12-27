// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/PsychokineticPropBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PsychokineticThrowableProp.generated.h"

class UProjectileMovementComponent;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API APsychokineticThrowableProp : public APsychokineticPropBase
{
	GENERATED_BODY()

public:
	APsychokineticThrowableProp();

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditDefaultsOnly)
	float FloatingHeight = 300.f;
	
	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY()
	AActor* CurrentTarget;
	TOptional<FVector> CurrentTargetLocation;
	bool bIsAttached = false;

public:
	FORCEINLINE void Attached() { bIsAttached = true; }
	FORCEINLINE bool IsAttached() const { return bIsAttached; }
	FORCEINLINE void SetTarget(AActor* Target) {CurrentTarget = Target;}
	FORCEINLINE void SetTarget(const FVector& TargetVector) {CurrentTargetLocation = TargetVector;}
	

	void OnStartGrab();
	UFUNCTION(BlueprintCallable)
	void OnHit();
	
	void OnChargingCancel();

	void FloatingTick(float DeltaTime);
	void Launch();
	
};

