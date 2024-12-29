// Fill out your copyright notice in the Description page of Project Settings.


#include "ScarletNexusGameMode.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"

void AScarletNexusGameMode::BP_BindFunctionWithAttributeChangeDelegate(AActor* InActor,
                                                                       const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute,
                                                                       FOnPercentValueChanged OnPercentValueChanged)
{
	auto ASC = UBaseFunctionLibrary::NativeGetAbilitySystemComponentFromActor(InActor);
	ASC->GetGameplayAttributeValueChangeDelegate(InCurrentAttribute).AddLambda([InActor, InMaxAttribute, OnPercentValueChanged](const FOnAttributeChangeData& ChangeData)
	{
		bool IsFound = false;
		float MaxValue = UAbilitySystemBlueprintLibrary::GetFloatAttribute(InActor, InMaxAttribute, IsFound);
		if (IsFound)
		{
			//Debug::Print(FString::Printf(TEXT("%s Gauage: %f"),*ChangeData.Attribute.GetName(), ChangeData.NewValue / MaxValue));
			OnPercentValueChanged.ExecuteIfBound(ChangeData.NewValue / MaxValue);
		}
	});
}
