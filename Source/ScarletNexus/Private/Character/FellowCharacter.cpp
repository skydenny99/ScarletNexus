// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FellowCharacter.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "BaseDebugHelper.h"

void AFellowCharacter::SetWeaponVisibility(bool Visibility)
{
	if (Weapon)
	{
		Weapon->SetVisibility(Visibility, true);
	}

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
