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
	UProjectileMovementComponent* ProjectileMovementComponent;
	AActor* TargetActor;
	bool bIsAttached = false;

public:
	FORCEINLINE void Attached() { bIsAttached = true; }
	FORCEINLINE bool IsAttached() const { return bIsAttached; }
	FORCEINLINE void SetTarget(AActor* Target) {TargetActor = Target;}
	void Launch();
	
};

