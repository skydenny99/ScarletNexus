// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "Components/ActorComponent.h"
#include "ComboSystemComponent.generated.h"


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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combo", meta=(AllowPrivateAccess=true))
	FComboCounter WeaponGroundCombo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combo", meta=(AllowPrivateAccess=true))
	FComboCounter WeaponAerialCombo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combo", meta=(AllowPrivateAccess=true))
	FComboCounter PsychGroundCombo;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combo", meta=(AllowPrivateAccess=true))
	FComboCounter PsychAerialCombo;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combo", meta=(AllowPrivateAccess=true))
	int32 CurrentBackstepAttackCount;

	float ActionElapsedTime;
	float ChargeAttackThreshold = 0.3f;
	FGameplayTag LastActivatedGameplayTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameplayAbilityBase> WeaponGroundAttackAbility;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameplayAbilityBase> WeaponAerialAttackAbility;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameplayAbilityBase> WeaponBackstepAbility;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameplayAbilityBase> WeaponChargeAttackAbility;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameplayAbilityBase> PsychGroundAttackAbility;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameplayAbilityBase> PsychAerialAttackAbility;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(AllowPrivateAccess=true))
	TSubclassOf<UGameplayAbilityBase> PsychSpecialAttackAbility;
	

public:
	void GrantAttackAbilites(UAbilitySystemComponent* ASC, int32 Level = 1);
	void TryActivateAbilityByInputTag(FGameplayTag tag);
	
	void UpdateInfoByUnlock();
	
	UFUNCTION()
	void ResetAllCombo(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);
	
	void ResetAttackCombo();

	UFUNCTION()
	void ResetBackstepCount();

	void ProcessInputAction(FGameplayTag ActionTag, ETriggerEvent TriggerEvent, const FInputActionInstance& Instance);
	bool ShouldBlockInputAction();

	UFUNCTION(BlueprintCallable, Category="Combo")
	void IncreaseCombo(UPARAM(ref) FComboCounter& ComboCounter);
};
