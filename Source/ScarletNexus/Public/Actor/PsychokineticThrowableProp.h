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

	virtual void BeginPlay() override;

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
	
	// void OnComponentHit()override;
	
	UFUNCTION(BlueprintCallable)
	void OnHit();


	UFUNCTION()
	void OnMeshHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		FVector NormalImpulse,
		const FHitResult& Hit
	);
	
	void OnChargingCancel();

	void FloatingTick(float DeltaTime);
	void Launch();
	
};

