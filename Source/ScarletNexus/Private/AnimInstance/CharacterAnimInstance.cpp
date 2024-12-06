// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/CharacterAnimInstance.h"
#include "Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseDebugHelper.h"
#include "KismetAnimationLibrary.h"

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


	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
	
	FVector MovementDir = OwningMovementComponent->GetLastInputVector();

	FVector Velocity = OwningCharacter->GetVelocity();
	Debug::Print(FString::Printf(TEXT("Locomotion Direction: %f"), LocomotionDirection));
}
