// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PsychokinesisComponent.generated.h"

class USphereComponent;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPsychTargetUpdated, AActor*)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCARLETNEXUS_API UPsychokinesisComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPsychokinesisComponent();

protected:
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* DetectionBoundary;
	
	UPROPERTY()
	TArray<AActor*> PsychTargetCandidates;
	UPROPERTY()
	AActor* PsychTarget;

	
	
	float UpdateInterval = 0.2f;
	FTimerHandle UpdateTimer;

	void UpdateNearestPsychTarget();
	
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
public:
	void InitBoundary(USphereComponent* InDetectionBoundary);
	FOnPsychTargetUpdated OnPsychTargetUpdated;

	UFUNCTION(BlueprintPure)
	FORCEINLINE AActor* GetPsychTarget() const {return PsychTarget;}
		
};
