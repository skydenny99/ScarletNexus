// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/DataAsset_InputConfig.h"


UInputAction* UDataAsset_InputConfig::GetInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FInputActionConfig& Config : NativeInputActions)
	{
		if (Config.InputTag == InInputTag && Config.InputAction)
			return Config.InputAction;
	}
	return nullptr;
}
