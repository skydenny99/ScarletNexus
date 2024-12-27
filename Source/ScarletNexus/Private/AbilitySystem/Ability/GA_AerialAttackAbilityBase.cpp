// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_AerialAttackAbilityBase.h"

#include "BaseDebugHelper.h"
#include "Character/Character_Kasane.h"
#include "Components/ComboSystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UGA_AerialAttackAbilityBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                                                const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	MovementComponent = Kasane->GetCharacterMovement();
	OriginGravityScale = MovementComponent->GravityScale;
}

void UGA_AerialAttackAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	MovementComponent->Velocity = FVector::ZeroVector;
	MovementComponent->GravityScale = 0.f;
	ComboSystem->ResetGroundCombo();
}

void UGA_AerialAttackAbilityBase::OnEndAbility(UGameplayAbility* Ability)
{
	Super::OnEndAbility(Ability);
	MovementComponent->Velocity = FVector::ZeroVector;
	MovementComponent->GravityScale = OriginGravityScale;
}
