// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter/BaseEnemyCharacter.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "AbilitySystem/Attribute/EnemyAttributeSet.h"
#include "BaseDebugHelper.h"
#include "Components/WidgetComponent.h"
#include "Components/UI/EnemyUIComponent.h"
#include "Components/SphereComponent.h"

ABaseEnemyCharacter::ABaseEnemyCharacter()
{
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));

	BaseAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("EnemyAttributeSet"));

	HealthComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthComponent"));
	HealthComponent->SetupAttachment(GetMesh());
	
	NoticeComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NoticeComponent"));
	NoticeComponent->SetupAttachment(GetMesh());

	LockOnComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("LockOnComponent"));
	LockOnComponent->SetupAttachment(GetMesh());
	
	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));

	CollisionSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphereComponent"));
	CollisionSphereComponent->SetupAttachment(RootComponent);

	CollisionSphereComponent->SetWorldScale3D(FVector(50.0f, 50.0f, 50.0f));
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

UPawnUIComponent* ABaseEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}



