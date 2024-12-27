// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "FellowCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UFellowCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
public:
	//HitDetection
	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InterectedActor) override;


	
	
};
