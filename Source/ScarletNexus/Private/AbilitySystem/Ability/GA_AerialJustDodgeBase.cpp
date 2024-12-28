// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_AerialJustDodgeBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BaseGameplayTags.h"
#include "Character/Character_Kasane.h"
#include "GameFramework/Character.h"

void UGA_AerialJustDodgeBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if (Kasane)
	{
		Kasane->MovementModeChangedDelegate.AddDynamic(this, &UGA_AerialJustDodgeBase::OnGrounded);
	}
}

void UGA_AerialJustDodgeBase::OnGrounded(ACharacter* Character, EMovementMode PrevMovementMode,
                                         uint8 PreviousCustomMode)
{
	if (PrevMovementMode == MOVE_Falling)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Character, BaseGameplayTags::Shared_Event_Grounded, FGameplayEventData());
	}
}
