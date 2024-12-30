// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "TargetTrackingSpringArmComponent.generated.h"

USTRUCT(BlueprintType)
struct FTrackingBoundary
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	float BoundaryLeft = 0.2f;
	
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	float BoundaryRight = 0.2f;
	
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	float BoundaryTop = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, meta = (UIMin = "0.0", UIMax = "1.0", ClampMin = "0.0", ClampMax = "1.0"))
	float BoundaryBottom = 0.4f;
};

DECLARE_DELEGATE_OneParam(FOnTargetUpdated, AActor*);
DECLARE_DELEGATE_OneParam(FOnTargetingActivated, bool);
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UTargetTrackingSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	bool bIsTargetTracking = false;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> FoundTargets;

	UPROPERTY(EditDefaultsOnly)
	FTrackingBoundary TrackingBoundary;
	
	int32 TargetIndex = 0;
	UPROPERTY()
	AActor* TargetActor = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float ResetThreshold = 0.1f;
	float ResetTimer = 0.f;
	bool bUpdateCameraTracking = false;

	bool bOverrideTrackingTarget = false;
	FTrackingBoundary OverrideTrackingBoundary {0.4, 0.4, 0.3, 0.5};
	UPROPERTY()
	AActor* OverrideTargetActor = nullptr;
	
	

protected:
	virtual FRotator GetDesiredRotation() const override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	FORCEINLINE void SetFoundTargets(const TArray<AActor*>& Targets) { FoundTargets = Targets; }
	void SortByDistance();
	void ChangeTarget(bool bIsLeft = true);
	void ToggleTargetTracking();
	void SetTargetTracking(bool IsTargetTracking);
	void SetTargetTrackingByAttack(AActor* AttackTarget);
	FORCEINLINE void StartResetTimer() { ResetTimer = 0.f; }
	AActor* GetTestTarget() const {return FoundTargets.IsEmpty() ? nullptr : FoundTargets.Last();}
	AActor* GetCurrentTarget();

	FORCEINLINE void ActivateOverrideTracking(bool InActivate) { bOverrideTrackingTarget = InActivate; }
	FORCEINLINE void SetOverrideTargetActor(AActor* InTargetActor) { OverrideTargetActor = InTargetActor; }
};


