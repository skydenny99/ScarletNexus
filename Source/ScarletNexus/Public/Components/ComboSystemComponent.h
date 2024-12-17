// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "Components/ActorComponent.h"
#include "ComboSystemComponent.generated.h"


class UDataAsset_AttackAbility;

USTRUCT(BlueprintType)
struct FComboCounter
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo")
	int32 CurrentComboCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combo")
	int32 MaxComboCount;

};

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
	UBaseAbilitySystemComponent* BaseAbilitySystemComponent;
	TMap<FGameplayTag, FGameplayAbilitySpec> AbilitySpecs;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combo")
	FComboCounter WeaponGroundCombo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combo")
	FComboCounter WeaponAerialCombo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combo")
	FComboCounter PsychGroundCombo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combo")
	FComboCounter PsychAerialCombo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combo")
	FComboCounter BackstepGroundCombo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combo")
	FComboCounter BackstepAerialCombo;

private:
	float ActionElapsedTime;
	float ChargeAttackThreshold = 0.3f;
	FGameplayTag LastActivatedGameplayTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(AllowPrivateAccess=true))
	UDataAsset_AttackAbility* AbilityAsset;
	

public:
	void GrantAttackAbilites(UAbilitySystemComponent* ASC, int32 Level = 1);
	void TryActivateAbilityByInputTag(FGameplayTag tag);
	bool TryCancelAttackAbility();
	
	void UpdateInfoByUnlock();
	
	UFUNCTION()
	void OnMovementModeChange(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);
	

	void ProcessInputAction(FGameplayTag ActionTag, ETriggerEvent TriggerEvent, const FInputActionInstance& Instance);
	bool ShouldBlockInputAction();

	UFUNCTION(BlueprintCallable, Category="Combo")
	void IncreaseCombo(UPARAM(ref) FComboCounter& ComboCounter);

	FORCEINLINE FGameplayTag GetAttackType() const {return LastActivatedGameplayTag;}

	void ResetGroundCombo();
	void ResetAerialCombo();
};
