// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_JumpBase.h"
#include "Character/Character_Kasane.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseDebugHelper.h"

void UGA_JumpBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	Kasane = Cast<ACharacter_Kasane>(ActorInfo->AvatarActor);
	check(Kasane);
	MovementComponent = Kasane->GetCharacterMovement();
	Kasane->JumpMaxCount = JumpPower.Num();
}

bool UGA_JumpBase::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
	{
		if (MovementComponent)
		{
			return MovementComponent->IsJumpAllowed() && Kasane->JumpCurrentCount < Kasane->JumpMaxCount;
		}
	}
	return false;
}

void UGA_JumpBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{			
		constexpr bool bReplicateEndAbility = true;
		constexpr bool bWasCancelled = true;
		EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}
	
	if (MovementComponent)
	{
		MovementComponent->JumpZVelocity = JumpPower[Kasane->JumpCurrentCount];
		Kasane->Jump();
		FTimerDelegate Dele;
		Dele.BindUObject(this, &UGA_JumpBase::EndAbility, Handle, ActorInfo, ActivationInfo, false, false);
		GetWorld()->GetTimerManager().SetTimer(ResetJumpTimer, Dele, 0.3f, false);
		//EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
	}
}


void UGA_JumpBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if (MovementComponent)
	{
		Kasane->StopJumping();
	}
}
