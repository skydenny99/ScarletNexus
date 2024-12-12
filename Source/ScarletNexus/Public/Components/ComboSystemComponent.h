// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "ComboSystemComponent.generated.h"


class ACharacter_Kasane;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCARLETNEXUS_API UComboSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this component's properties
	UComboSystemComponent();

private:
	ACharacter_Kasane* Kasane;
	
	int32 CurrentGroundComboCount;
	int32 CurrentAerialComboCount;
	int32 CurrentBackstepAttackCount;
	

public:
	void ActivateAbilityByTag(FGameplayTag tag);
	
	void UpdateInfoByUnlock();
	
	UFUNCTION()
	void ResetAllCombo(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);
	
	void ResetAttackCombo();

	UFUNCTION()
	void ResetBackstepCount();
};
