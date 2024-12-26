// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter/BaseEnemyCharacter.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "AbilitySystem/Attribute/EnemyAttributeSet.h"
#include "BaseDebugHelper.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));

	BaseAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("EnemyAttributeSet"));
	
}

void ABaseEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (StartupData.IsNull() == false)
	{
		if (UDataAsset_StartupBase* LoadedData = StartupData.LoadSynchronous())
		{
			LoadedData->GiveStartupAbilities(BaseAbilitySystemComponent);
			
			Debug::Print(TEXT("Enemy Start Up Data Loaded"), FColor::Green);
		}
	}

	
}

UPawnCombatComponent* ABaseEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

FVector ABaseEnemyCharacter::GetTargetVector() const
{
	FVector TargetVector = MainBody->GetBoneLocation("Target");
	return TargetVector;
}

