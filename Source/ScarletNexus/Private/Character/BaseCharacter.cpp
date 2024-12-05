// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "DataAsset/DataAsset_StartupBase.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return GetBaseAbilitySystemComponent();
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (BaseAbilitySystemComponent)
	{
		BaseAbilitySystemComponent->InitAbilityActorInfo(this, this);
		if (StartupData.IsNull() == false)
		{
			if (UDataAsset_StartupBase* LoadedData = StartupData.LoadSynchronous())
			{
				LoadedData->GiveStartupAbilities(BaseAbilitySystemComponent);
			}
		}
	}
}
