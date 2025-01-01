// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/PsychokineticPropBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PsychokineticThrowableProp.generated.h"

class UWidgetComponent;
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
	int32 CurrentControlNum = 0;
	int32 MaxControlNum = 5;

	UPROPERTY(EditDefaultsOnly)
	bool bCanClonable = true;
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditDefaultsOnly)
	float FloatingHeight = 150.f;
	
	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UWidgetComponent* InterectComponent;

	UPROPERTY()
	AActor* CurrentTarget;
	TOptional<FVector> CurrentTargetLocation;
	FVector CachedLaunchedLocation;
	FRotator CachedLaunchedRotation;
	bool bIsAttached = false;

public:
	FORCEINLINE void Attached() { bIsAttached = true; }
	FORCEINLINE bool IsAttached() const { return bIsAttached; }
	FORCEINLINE void SetTarget(AActor* Target)
	{
		CurrentTargetLocation.Reset();
		CurrentTarget = Target;
	}
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
	void Launch(bool NeedToClone, bool DoubleClone = false);
	void CloneLaunch();
	
};

