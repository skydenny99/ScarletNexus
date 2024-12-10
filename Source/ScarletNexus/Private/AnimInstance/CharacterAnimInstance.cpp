// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/CharacterAnimInstance.h"
#include "Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseDebugHelper.h"
#include "KismetAnimationLibrary.h"
#include "BaseFunctionLibrary.h"
#include "BaseGameplayTags.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (OwningCharacter == nullptr || OwningMovementComponent == nullptr)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	bIsGrounded = OwningMovementComponent->IsFalling() == false;

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
	if (OwningMovementComponent->IsWalking())
	{
		if (UBaseFunctionLibrary::NativeActorHasTag(OwningCharacter, BaseGameplayTags::Player_Status_Move_Dash))
		{
			CharacterSpeedType = ECharacterSpeedType::Dash;
		}
		else
		{
			if (GroundSpeed > 100)
			{
				CharacterSpeedType = ECharacterSpeedType::Run;
			}
			else
			{
				CharacterSpeedType = ECharacterSpeedType::Walk;
			}
		}
	}
	else
	{
		CharacterSpeedType = ECharacterSpeedType::Idle;
	}


	FVector MovementDir = OwningMovementComponent->GetLastInputVector();

	FVector Velocity = OwningCharacter->GetVelocity();
	//Debug::Print(FString::Printf(TEXT("Last Input Direction, X: %f, Y:%f"), MovementDir.X, MovementDir.Y), FColor::Red);
	//Debug::Print(FString::Printf(TEXT("Locomotion Direction: %f"), LocomotionDirection), FColor::Green);
}
