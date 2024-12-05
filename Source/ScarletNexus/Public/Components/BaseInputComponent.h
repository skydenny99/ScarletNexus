// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/DataAsset_InputConfig.h"
#include "BaseInputComponent.generated.h"


/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UBaseInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc InputFunc);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputTriggeredFunc);
};

template<class UserObject, typename CallbackFunc>
inline void UBaseInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc InputFunc)
{
	if (auto InputAction = InInputConfig->GetInputActionByTag(InInputTag))
	{
		BindAction(InputAction, TriggerEvent, ContextObject, InputFunc);
	}
}

template<class UserObject, typename CallbackFunc>
inline void UBaseInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputTriggeredFunc)
{
	check(InInputConfig);

	for (const FInputActionConfig& Config : InInputConfig->AbilityInputActions)
	{
		if (Config.IsValid() == false) continue;
		BindAction(Config.InputAction, ETriggerEvent::Triggered, ContextObject, InputTriggeredFunc, Config.InputTag);
	}
}
