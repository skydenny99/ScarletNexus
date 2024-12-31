// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "BaseType/BaseEnumType.h"
#include "BaseFunctionLibrary.generated.h"

class UBaseAbilitySystemComponent;
class UPawnCombatComponent;


/**
 *
 */
UCLASS()
class SCARLETNEXUS_API UBaseFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// UBlueprintFunctionLibrary�� ���� �����̹Ƿ� public�� static���� �����ؾ���. ���ͷ� ������ �����Ƽ�ý��� ������Ʈ ��������.
	static UBaseAbilitySystemComponent* NativeGetAbilitySystemComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void AddPlaygameTagToActor(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void RemovePlayGameTagFromActor(AActor* Actor, FGameplayTag Tag);

	static bool NativeActorHasTag(AActor* Actor, FGameplayTag Tag);

	static bool NativeActorHasAnyTags(AActor* Actor, FGameplayTagContainer Tags);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (Display = "Does Actor Has Tag", ExpandEnumAsExecs = "OutType"))
	static void BP_HasTag(AActor* Actor, FGameplayTag Tag, EBaseConfirmType& OutType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (Display = "Get PawnCombatComponent From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* Actor, EBaseValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "FunctionLibrary")
	static EBaseAIDirectionType ComputeAIDirection(AActor* Target, AActor* SelfActor, float& OutAngleDifference);


	UFUNCTION(BlueprintPure, Category = "FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* Instigator, AActor* TargetActor, const FGameplayEffectSpecHandle& OutSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static AActor* GetNearestActorFromTarget(TArray<AActor*> Candidates, AActor* TargetActor);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static bool TryCancelAllAbilityByTag(AActor* Actor, FGameplayTag Tag);
};
