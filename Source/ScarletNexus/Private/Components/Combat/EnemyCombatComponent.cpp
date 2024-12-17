// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BaseDebugHelper.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "BaseGameplayTags.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	Debug::Print(GetOwningPawn()->GetActorLabel() + " Hit " + HitActor->GetActorLabel(), FColor::Black);
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}

	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), BaseGameplayTags::Shared_Event_Hit_Normal, Data);
}

void UEnemyCombatComponent::OnWeaponPulledFromTargetActor(AActor* InterectedActor)
{
	Debug::Print(GetOwningPawn()->GetActorLabel() + "  weapon pulled from " + InterectedActor->GetActorLabel(), FColor::White);
}
