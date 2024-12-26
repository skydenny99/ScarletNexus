// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/DataAsset_InputConfig.h"
#include "DataAsset/DataAsset_DirectionInputConfig.h"
#include "Character/Character_Kasane.h"
#include "BaseInputComponent.generated.h"

class UComboSystemComponent;
class UDataAsset_DirectionInputConfig;
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

	template<class UserObject, typename CallbackFunc>
	void BindDirectionInput(const UDataAsset_DirectionInputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputTriggeredFunc);

	template<class UserObject>
	void BindActionInstanceWithTag(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject);
};

template<class UserObject, typename CallbackFunc>
inline void UBaseInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc InputFunc)
{
	check(InInputConfig);
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

template <class UserObject, typename CallbackFunc>
void UBaseInputComponent::BindDirectionInput(const UDataAsset_DirectionInputConfig* InInputConfig,
	UserObject* ContextObject, CallbackFunc InputTriggeredFunc)
{
	check(InInputConfig);
	for (auto DirectionInputConfig : InInputConfig->DirectionInputMap)
	{
		BindAction(DirectionInputConfig.Value, ETriggerEvent::Triggered, ContextObject, InputTriggeredFunc, DirectionInputConfig.Key);
	}
}

template <class UserObject>
void UBaseInputComponent::BindActionInstanceWithTag(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject)
{
	check(InInputConfig);
	
	for (auto InputConfig : InInputConfig->AttackInputActions)
	{
		BindActionInstanceLambda(InputConfig.InputAction, ETriggerEvent::Triggered,
			[InputConfig, ContextObject] (const FInputActionInstance& ActionInstance)
			{
				ContextObject->OnAttackInputTriggered(InputConfig.InputTag, ActionInstance);
			});
		
		BindActionInstanceLambda(InputConfig.InputAction, ETriggerEvent::Completed,
			[InputConfig, ContextObject] (const FInputActionInstance& ActionInstance)
			{
				ContextObject->OnAttackInputCompleted(InputConfig.InputTag, ActionInstance);
			});
	}
}
