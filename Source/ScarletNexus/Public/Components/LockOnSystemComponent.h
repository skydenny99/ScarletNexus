// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnSystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeTarget, AActor*)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCARLETNEXUS_API ULockOnSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULockOnSystemComponent();

private:

	UPROPERTY(VisibleAnywhere)
	AActor* CurrentTarget;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> TargetList;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectQueries;
	TArray<AActor*> IgnoreActors;
	int32 CurrentTargetIndex;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FOnChangeTarget OnChangeTarget;

	void OnAttackTarget(AActor* Target);
	void OnTargetDeath(AActor* Target);
	UFUNCTION(BlueprintCallable)
	AActor* GetNearestTarget();

	UFUNCTION(BlueprintCallable)
	AActor* SwitchTarget(bool bLeft);

	FORCEINLINE AActor* GetCurrentTarget() { return CurrentTarget; }
};
