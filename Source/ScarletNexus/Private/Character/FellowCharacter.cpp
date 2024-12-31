// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FellowCharacter.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "BaseDebugHelper.h"
#include "Components/Combat/FellowCombatComponent.h"
#include "AbilitySystem/Attribute/PlayerAttributeSet.h"
#include "Components/UI/PlayerUIComponent.h"
#include "Components/UI/PawnUIComponent.h"


AFellowCharacter::AFellowCharacter()
{
	
	FellowCombatComponent = CreateDefaultSubobject<UFellowCombatComponent>(TEXT("FellowCombatComponent"));
 
	BaseAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));

	PlayerUIComponent = CreateDefaultSubobject<UPlayerUIComponent>(TEXT("PlayerUIComponent"));
}

void AFellowCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (StartupData.IsNull() == false)
	{
		if (UDataAsset_StartupBase* LoadedData = StartupData.LoadSynchronous())
		{
			LoadedData->GiveStartupAbilities(BaseAbilitySystemComponent);
		}
	}
}

UPawnCombatComponent* AFellowCharacter::GetPawnCombatComponent() const
{
	return  FellowCombatComponent;
}



UPawnUIComponent* AFellowCharacter::GetPawnUIComponent() const
{
	return PlayerUIComponent;
}

UPlayerUIComponent* AFellowCharacter::GetPlayerUIComponent() const
{
	return PlayerUIComponent;
}
