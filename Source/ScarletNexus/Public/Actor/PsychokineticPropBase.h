// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PsychokineticPropBase.generated.h"

class APsychokineticPropBase;
DECLARE_DELEGATE_OneParam(FOnUsePsychProp, APsychokineticPropBase*);

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

	UPROPERTY(EditDefaultsOnly, meta=(ClampMin="0.15"))
	float ChargeTime = 1.f;

	UPROPERTY(EditDefaultsOnly)
	int32 PsychCost = 10;
	bool bIsUsed = false;
	
public:
	FOnUsePsychProp OnUsePsychProp;
	
	void DissolveProp();
	FORCEINLINE float GetChargeTime() const { return ChargeTime; }
	FORCEINLINE bool IsUsed() const { return bIsUsed; }
};
