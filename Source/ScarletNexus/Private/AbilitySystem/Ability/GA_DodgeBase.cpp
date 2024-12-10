// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_DodgeBase.h"
#include "Animation/AnimMontage.h"
#include "Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UGA_DodgeBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	DodgeCharacter = GetOwnerWithCasting<ABaseCharacter>();
	check(DodgeCharacter);
	DodgeMovementComponent = DodgeCharacter->GetCharacterMovement();
}

void UGA_DodgeBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	

}

void UGA_DodgeBase::AlignCharacterWithCameraDirection()
{
	FVector KeyDirection = FVector(0, 0, 0);
	
	
}

void UGA_DodgeBase::GetCurrentCharacterLookDirection(const EBaseDirectionType& DirectionResult)
{
	
}
