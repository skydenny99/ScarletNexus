// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter/BaseEnemyCharacter.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAsset/DataAsset_StartupBase.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
}

void ABaseEnemyCharacter::PossessedBy(AController* NewController)
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

UPawnCombatComponent* ABaseEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}
