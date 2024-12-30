// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "Character/Character_Kasane.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PsychAbilityHelperLibrary.generated.h"

class UGameplayEffect;
class ACharacter_Kasane;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UPsychAbilityHelperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void NativeSetPsychObject(const ACharacter_Kasane* Kasane, AActor* PsychObject);
	static bool NativeHasPsychokineticThrowablePropInRange(const ACharacter_Kasane* Kasane);
	static bool NativeHasPsychokineticSpecialPropInRange(const ACharacter_Kasane* Kasane);
	static void NativeOnActivateNormalPsychAbility(const ACharacter_Kasane* Kasane);
	static void NativeOnActivateSpecialPsychAbility(const ACharacter_Kasane* Kasane);
	static void NativeOnChargingCancelPsychAbility(const ACharacter_Kasane* Kasane);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void ActivateThrowPsychAbility(ACharacter_Kasane* Kasane);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void SetPropDamageHandle(UGameplayAbility* Ability, ACharacter_Kasane* Kasane, float Level, TSubclassOf<UGameplayEffect> DamageEffectClass);
	
	static void ActivateSpecialPsychAbility();

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void SetBlockUpdateTarget(const ACharacter_Kasane* Kasane, bool InBlock);

	static UGameplayEffect* CreatePsychCostGameplayEffect(const ACharacter_Kasane* Kasane);
	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void ApplyPsychCostGameplayEffect(const ACharacter_Kasane* Kasane);
};