// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SASManageComponent.h"

#include "BaseDebugHelper.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Character/Character_Kasane.h"
#include "DataAsset/DataAsset_SASAbility.h"

// Sets default values for this component's properties
USASManageComponent::USASManageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USASManageComponent::ToggleSASAbility(FGameplayTag InInputTag)
{
	int32 AbilityIndex = 0;
	if (InInputTag.MatchesTagExact(BaseGameplayTags::InputTag_SAS_Second))
	{
		AbilityIndex = 1;
	}
	else if (InInputTag.MatchesTagExact(BaseGameplayTags::InputTag_SAS_Third))
	{
		AbilityIndex = 2;
	}
	else if (InInputTag.MatchesTagExact(BaseGameplayTags::InputTag_SAS_Fourth))
	{
		AbilityIndex = 3;
	}

	if (CurrentSASAbilityTags.IsValidIndex(AbilityIndex) == false) return; 
	FGameplayTag AbilityTag = CurrentSASAbilityTags[AbilityIndex];
	
	if (AbilityTag.IsValid() == false || AbilitySpecs.Contains(AbilityTag) == false)
	{
		Debug::Print("SAS Ability not found", FColor::Red);
		return;
	}
	
	if (BaseAbilitySystemComponent->IsAbilityActive(AbilitySpecs[AbilityTag].Handle))
	{
		Debug::Print("SAS Ability is activated", FColor::Red);
		BaseAbilitySystemComponent->CancelAbilityHandle(AbilitySpecs[AbilityTag].Handle);
	}
	else
	{
		Debug::Print("SAS Ability not is activated", FColor::Red);
		if (BaseAbilitySystemComponent->TryActivateAbility(AbilitySpecs[AbilityTag].Handle) == false)
		{
			Debug::Print("SAS Ability try failed", FColor::Red);
		}
	}
}

void USASManageComponent::CancelAllSASAbilities()
{
	for (auto Pair : AbilitySpecs)
	{
		if (BaseAbilitySystemComponent->IsAbilityActive(AbilitySpecs[Pair.Key].Handle))
		{
			BaseAbilitySystemComponent->CancelAbilityHandle(Pair.Value.Handle);
		}
	}
}

void USASManageComponent::InitReferences(ACharacter_Kasane* InKasane)
{
	Kasane = InKasane;
	if (Kasane)
	{
		BaseAbilitySystemComponent = Kasane->GetBaseAbilitySystemComponent();
	}
	
}

void USASManageComponent::GrantSASAbilites(int32 Level)
{
	check(AbilityAsset);
	for (auto AbilityClass : AbilityAsset->SASAbilityList)
	{
		if (AbilityClass == nullptr) continue;
		FGameplayAbilitySpec Spec(AbilityClass);
		Spec.SourceObject = BaseAbilitySystemComponent->GetAvatarActor();
		Spec.Level = Level;
		BaseAbilitySystemComponent->GiveAbility(Spec);
		AbilitySpecs.Add(Spec.Ability->AbilityTags.First(), Spec);
	}
}

void USASManageComponent::OnSASInputTriggered(FGameplayTag InInputTag)
{
	if (InInputTag.IsValid() == false || UBaseFunctionLibrary::NativeActorHasTag(Kasane, BaseGameplayTags::Shared_Status_Direct)) return;
	if (InInputTag.MatchesTagExact(BaseGameplayTags::InputTag_SAS_Cancel))
	{
		CancelAllSASAbilities();
	}
	else
	{
		ToggleSASAbility(InInputTag);
		OnSASTrigger.Broadcast(InInputTag);
	}
}


