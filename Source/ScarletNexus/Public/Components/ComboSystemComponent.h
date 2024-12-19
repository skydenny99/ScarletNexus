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
	virtual void BeginPlay() override;

	ACharacter_Kasane* Kasane;
	UBaseAbilitySystemComponent* BaseAbilitySystemComponent;
	TMap<FGameplayTag, FGameplayAbilitySpec> AbilitySpecs;

	bool bIsComboAttacking = false;
	

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
	UPROPERTY(BlueprintReadWrite, Category="Charge", meta=(AllowPrivateAccess=true))
	bool bIsCharging = false;
	bool bIsAutoCompletion = false;
	
	float ActionElapsedTime;
	float ChargeAttackThreshold = 0.3f;
	float ChargeCompletionTime = 0.1f;
	FGameplayTag LastActivatedGameplayTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability", meta=(AllowPrivateAccess=true))
	UDataAsset_AttackAbility* AbilityAsset;
	

public:
	void GrantAttackAbilites(UAbilitySystemComponent* ASC, int32 Level = 1);
	void UpdateInfoByUnlock();
	
	void TryActivateAbilityByInputTag(FGameplayTag tag);
	void TryActivateChargeAbility();
	bool TryCancelAttackAbility();
	
	UFUNCTION()
	void OnMovementModeChange(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);
	

	void ProcessInputAction(FGameplayTag ActionTag, ETriggerEvent TriggerEvent, const FInputActionInstance& Instance);
	bool ShouldBlockInputAction();

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

	void SetupChargeProperty(float CompletionTime, bool AutoCompletion = true)
	{
		ActionElapsedTime = CompletionTime;
		bIsAutoCompletion = AutoCompletion;
	}
	
	UFUNCTION(BlueprintCallable, Category="Combo", meta=(ExpandBoolAsExecs = "InCombo"))
	void IsComboAttacking(bool& InCombo) { InCombo = bIsComboAttacking; }
};
