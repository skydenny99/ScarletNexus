// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_GetDistanceToTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UBTS_GetDistanceToTargetActor : public UBTService
{
	GENERATED_BODY()

public:
	UBTS_GetDistanceToTargetActor();

	UPROPERTY(EditAnywhere, Category = "Target")
	FBlackboardKeySelector InTargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Target")
	FBlackboardKeySelector OutDistanceKey;


	private:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
