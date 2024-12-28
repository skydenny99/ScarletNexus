// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
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
	virtual void BeginPlay() override;

	UPROPERTY()
	ACharacter_Kasane* Kasane;
	UPROPERTY()
	UBaseAbilitySystemComponent* BaseAbilitySystemComponent;
	TMap<FGameplayTag, FGameplayAbilitySpec> AbilitySpecs;

	bool bIsPsychComboAttacking = false;
	FTimerHandle PsychComboResetTimerHandle;
	float PsychComboResetTime = 3.f;

	FTimerHandle ComboDashAttackTimerHandle;
	float ComboDashResetTime = 1.f;

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
	bool bIsCharging = false;
	bool bIsAutoCompletion = false;
	bool bChargeAbilityAlreadyTriggered = false;
	
	float ActionElapsedTime;
	float StartActionElapsedTime;
	float ChargeAttackThreshold = 0.3f;
	float ChargeCompletionTime = 0.1f;

	FGameplayTag LastChargeAbilityInputTag;
	FGameplayTag LastActivatedGameplayTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(AllowPrivateAccess=true))
	UDataAsset_AttackAbility* AbilityAsset;

	UPROPERTY()
	USphereComponent* JustDodgeBoundary;

public:
	void InitReferences(ACharacter_Kasane* InKasane, USphereComponent* InJustDodgeBoundary);
	void GrantAttackAbilites(UAbilitySystemComponent* ASC, int32 Level = 1);
	void UpdateInfoByUnlock();

	bool TryActivateAbilityByInputTag(FGameplayTag tag);
	void TryActivateChargeAbility();
	bool TryCancelAttackAbility();
	
	UFUNCTION()
	void OnMovementModeChange(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);
	

	void ProcessInputAction(FGameplayTag InputTag, ETriggerEvent TriggerEvent, const FInputActionInstance& Instance);
	bool CheckJustDodge();

	UFUNCTION(BlueprintCallable, Category="Combo")
	void IncreaseCombo(UPARAM(ref) FComboCounter& ComboCounter);

	FORCEINLINE FGameplayTag GetAttackType() const {return LastActivatedGameplayTag;}
	UFUNCTION()
	FORCEINLINE void ResetActivateAbilityTag() {LastActivatedGameplayTag = FGameplayTag();}

	UFUNCTION(BlueprintCallable, Category="Combo")
	void ResetGroundCombo();
	
	UFUNCTION(BlueprintCallable, Category="Combo")
	void ResetAerialCombo();
	
	UFUNCTION(BlueprintCallable, Category="Combo")
	void ResetWeaponCombo();

	UFUNCTION(BlueprintCallable, Category="Combo")
	void ResetBackstep();

	void StartCharging()
	{
		bIsCharging = true;
		bChargeAbilityAlreadyTriggered = false;
	};
	void SetupChargeProperty(float CompletionTime, bool AutoCompletion = true)
	{
		ChargeCompletionTime = CompletionTime;
		bIsAutoCompletion = AutoCompletion;
	}

	UFUNCTION(BlueprintCallable, Category="Combo")
	void StartPsychComboTimer();

	UFUNCTION(BlueprintCallable, Category="Combo")
	void ClearPsychComboTimer();

	UFUNCTION(BlueprintCallable, Category="Combo")
	void StopPsychComboTimer();

	UFUNCTION(BlueprintCallable, Category="Combo")
	void StartComboDashAttackTimer();
	
	UFUNCTION(BlueprintCallable, Category="Combo", meta=(ExpandBoolAsExecs = "InCombo"))
	void IsPsychComboAttacking(bool& InCombo) { InCombo = bIsPsychComboAttacking; }

	UFUNCTION(BlueprintPure, Category="Combo")
	FORCEINLINE bool GetIsPsychComboAttacking() const { return bIsPsychComboAttacking; }
};
