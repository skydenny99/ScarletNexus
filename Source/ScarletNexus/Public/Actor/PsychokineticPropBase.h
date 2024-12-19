// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PsychokineticPropBase.generated.h"

UCLASS()
class SCARLETNEXUS_API APsychokineticPropBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APsychokineticPropBase();

protected:
	int32 CurrentControlNum = 0;
	int32 MaxControlNum = 5;

	UPROPERTY(EditDefaultsOnly)
	float ChargeTime = 1.f;
	UPROPERTY(EditDefaultsOnly)
	float FloatingHeight = 100.f;

	UPROPERTY(EditDefaultsOnly)
	int32 PsychCost = 10;
public:
	void ActivateControl();
	void DeactivateControl();
	void DissolveProp();

};
