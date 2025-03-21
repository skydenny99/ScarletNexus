// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/Attribute/BaseAttributeSet.h"
#include "DataAsset/DataAsset_StartupBase.h"
#include "BaseDebugHelper.h"
#include "Subsystem/TimeControlSubsystem.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	// BaseAttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributeSet"));
	
}

void ABaseCharacter::SetCustomTimeDilation(const ETimeDilationReason& Reason, float TimeDilation)
{
	if (AllowSetTimeDilation(Reason))
	{
		CustomTimeDilation = TimeDilation;
	}
	OnChangeCustomTimeDilationDelegate.Broadcast(Reason, TimeDilation);
}

bool ABaseCharacter::AllowSetTimeDilation(const ETimeDilationReason& Reason)
{
	return true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (auto TimeSubsystem = GetWorld()->GetSubsystem<UTimeControlSubsystem>())
	{
		TimeSubsystem->TimeDilationDelegate.AddUObject(this, &ABaseCharacter::SetCustomTimeDilation);
		SetCustomTimeDilation(TimeSubsystem->GetCurrentTimeDilationReason(), TimeSubsystem->GetCurrentCustomTimeDilation());
	}
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
	}
}

UPawnCombatComponent* ABaseCharacter::GetPawnCombatComponent() const
{
	// 부모클래스 재구현 X
	return nullptr;
}

UPawnUIComponent* ABaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
}

UPlayerUIComponent* ABaseCharacter::GetPlayerUIComponent() const
{
	return nullptr;
}
