// Fill out your copyright notice in the Description page of Project Settings.


#include "ScarletNexusGameMode.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "Character/Character_Kasane.h"

/*
AScarletNexusGameMode::AScarletNexusGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UMG_HUD(TEXT("WidgetBlueprint'/Game/UI/UI/UMG_HUD.UMG_HUD_C'"));
	if (UMG_HUD.Succeeded())
	{
		HUD_Class = UMG_HUD.Class;
	}
}

void AScarletNexusGameMode::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(GetWorld()->GetFirstPlayerController(), HUD_Class);
	HUD->AddToViewport();
}
*/

void AScarletNexusGameMode::BP_BindPercentWithAttributeChangeDelegate(AActor* InActor,
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

void AScarletNexusGameMode::BP_BindHealthPointWithAttributChangeDelegate(AActor* InActor,
																		const FGameplayAttribute InCurrentAttribute,
																		FOnfloatValueChanged OnFloatValueChanged)
{
	auto ASC = UBaseFunctionLibrary::NativeGetAbilitySystemComponentFromActor(InActor);
	ASC->GetGameplayAttributeValueChangeDelegate(InCurrentAttribute).AddLambda([InActor, OnFloatValueChanged](const FOnAttributeChangeData& ChangeData)
	{
		/*bool IsFound = false;
		float MaxValue = UAbilitySystemBlueprintLibrary::GetFloatAttribute(InActor, InMaxAttribute, IsFound);
		if (IsFound)
		{
			OnFloatValueChanged.ExecuteIfBound(ChangeData.NewValue);
		}*/
		OnFloatValueChanged.ExecuteIfBound(ChangeData.NewValue);
	});
}

/*
void AScarletNexusGameMode::BP_BindSASTopGaugeWithAttributeChangeDelegate(AActor* InActor,
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
*/

/*void AScarletNexusGameMode::BP_BindDebuffWithAttributeChanageDelegate(AActor* InActor,
		const FGameplayAttribute InCurrentAttribute, FOnDebuffChanged OnDebuffChanged)
{
	auto ASC = UBaseFunctionLibrary::NativeGetAbilitySystemComponentFromActor(InActor);
	ASC->GetGameplayAttributeValueChangeDelegate(InCurrentAttribute).AddLambda([InActor, OnDebuffChanged](const FOnAttributeChangeData& ChangeData)
	{
		bool IsFound = false;
		/*float MaxValue = UAbilitySystemBlueprintLibrary::
		if (IsFound)
		{
			OnDebuffChanged.ExecuteIfBound(ChangeData.NewValue);
		}#1#
	});
}

void AScarletNexusGameMode::BP_BindInitNameHpWithAttributChangeDelegate(AActor* InActor,
																		const FGameplayAttribute InCurrentAttribute, const FGameplayAttribute InMaxAttribute,
																		FOnNameHpChanged OnNameHpChanged)
{
	auto ASC = UBaseFunctionLibrary::NativeGetAbilitySystemComponentFromActor(InActor);
	ASC->GetGameplayAttributeValueChangeDelegate(InCurrentAttribute).AddLambda([InActor, InMaxAttribute, OnNameHpChanged](const FOnAttributeChangeData& ChangeData)
	{
		bool IsFound = false;
		float MaxValue = UAbilitySystemBlueprintLibrary::GetFloatAttribute(InActor, InMaxAttribute, IsFound);
		if (IsFound)
		{
			//2Param
			//OnNameHpChanged.ExecuteIfBound(ChangeData,ChangeData.NewValue);
		}
	});
}*/
