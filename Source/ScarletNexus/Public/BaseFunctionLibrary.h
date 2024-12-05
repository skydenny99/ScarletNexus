// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "BaseType/BaseEnumType.h"
#include "BaseFunctionLibrary.generated.h"

class UBaseAbilitySystemComponent;


/**
 *
 */
UCLASS()
class SCARLETNEXUS_API UBaseFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// UBlueprintFunctionLibrary는 내부 접근이므로 public과 static으로 접근해야함. 액터로 접근해 어빌리티시스템 컴포넌트 가져오기.
	static UBaseAbilitySystemComponent* NativeGetAbilitySystemComponentFromActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void AddPlaygameTagToActor(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void RemovePlayGameTagFromActor(AActor* Actor, FGameplayTag Tag);

	static bool NativeActorHasTag(AActor* Actor, FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (Display = "Does Actor Has Tag", ExpandEnumAsExecs = "OutType"))
	static void BP_HasTag(AActor* Actor, FGameplayTag Tag, EBaseConfirmType& OutType);

};
