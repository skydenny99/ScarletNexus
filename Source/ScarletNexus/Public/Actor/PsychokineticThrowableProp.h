// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Actor/PsychokineticPropBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PsychokineticThrowableProp.generated.h"

class UGameplayEffect;
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

	UPROPERTY(EditAnywhere)
	float Damage;


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

	UPROPERTY()
	AActor* CurrentTarget;
	TOptional<FVector> CurrentTargetLocation;
	FVector CachedLaunchedLocation;
	FRotator CachedLaunchedRotation;
	bool bIsAttached = false;

	UPROPERTY(BlueprintReadOnly, Category="Projectile", meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle PropDamageSpecHandle;
	
	UFUNCTION()
	void HandleApplyProp(APawn* HitPawn, FGameplayEventData& Payload);



public:
	FORCEINLINE void Attached() { bIsAttached = true; }
	FORCEINLINE bool IsAttached() const { return bIsAttached; }
	FORCEINLINE void SetTarget(AActor* Target)
	{
		CurrentTargetLocation.Reset();
		CurrentTarget = Target;
	}
	FORCEINLINE void SetTarget(const FVector& TargetVector) {CurrentTargetLocation = TargetVector;}
	FORCEINLINE void SetDamageHandle(const FGameplayEffectSpecHandle& Handle) {PropDamageSpecHandle = Handle;}




	UFUNCTION(BlueprintCallable)
	float GetDamage() {return Damage;}
	

	void OnStartGrab(bool NeedToClone, bool DoubleClone);
	
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
	void CloneLaunch();
	
};

