// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Ability/GA_Dodge_Player.h"

#include "BaseDebugHelper.h"
#include "BaseType/BaseEnumType.h"
#include "Character/BaseCharacter.h"
#include "Character/Character_Kasane.h"
#include "Kismet/KismetMathLibrary.h"


bool operator==(uint8 Lhs, EBaseDirectionType Type)
{
	return Lhs == static_cast<uint8>(Type);
}


bool UGA_Dodge_Player::CheckDirection(uint8 Lhs, EBaseDirectionType RHS) const
{
	uint8 tmp = !static_cast<uint8>(RHS);
	return (Lhs & tmp) == 0;
}

void UGA_Dodge_Player::GetCharacterDodgeDirection(EBaseDirectionType& DirectionResult)
{
	ACharacter_Kasane* Kasane = Cast<ACharacter_Kasane>(DodgeCharacter);
	check(Kasane);
	uint8 DirectionInput = Kasane->GetDirectionByHistory();
	if (DirectionInput == EBaseDirectionType::Max)
	{
		DirectionResult = EBaseDirectionType::Front;
		return;
	}
	
	
	FVector InputDirection(0.f);
	if (DirectionInput & (static_cast<uint8>(EBaseDirectionType::Front) & 0b0011))
	{
		InputDirection += FVector::ForwardVector;
	}
	
	if (DirectionInput & (static_cast<uint8>(EBaseDirectionType::Back) & 0b0011))
	{
		InputDirection += FVector::BackwardVector;
	}
	
	if (DirectionInput & (static_cast<uint8>(EBaseDirectionType::Right) & 0b1100))
	{
		InputDirection += FVector::RightVector;
	}
	
	if (DirectionInput & (static_cast<uint8>(EBaseDirectionType::Left) & 0b1100))
	{
		InputDirection += FVector::LeftVector;
	}


	FVector LookDirection = FRotator(0.f, DodgeCharacter->GetControlRotation().Yaw, 0.f).RotateVector(InputDirection);
	FVector CharacterForward = DodgeCharacter->GetActorForwardVector();
	CharacterForward -= DodgeCharacter->GetActorLocation();
	FVector CharacterRight = DodgeCharacter->GetActorRightVector();
	CharacterRight -= DodgeCharacter->GetActorLocation();

	FVector NearestVector;
	LookDirection.Normalize();
	float VerticalDot = FVector::DotProduct(LookDirection, CharacterForward);
	float HorizontalDot = FVector::DotProduct(LookDirection, CharacterRight);

	// Check Nearest Vector
	if (FMath::Abs(VerticalDot) >= FMath::Abs(HorizontalDot))
	{
		if (VerticalDot > 0.f) // Forward
		{
			NearestVector = CharacterForward;
			DirectionResult = EBaseDirectionType::Front;
			Debug::Print("Forward");
		}
		else // Backward
		{
			NearestVector = -CharacterForward;
			DirectionResult = EBaseDirectionType::Back;
			Debug::Print("Back");
			LookDirection = UKismetMathLibrary::RotateAngleAxis(LookDirection, 180, FVector::UpVector);
		}
	}
	else
	{
		if (HorizontalDot > 0.f) // Right
		{
			NearestVector = CharacterRight;
			DirectionResult = EBaseDirectionType::Right;
			Debug::Print("Right");	
			LookDirection = UKismetMathLibrary::RotateAngleAxis(LookDirection, -90, FVector::UpVector);
		}
		else // Left
		{
			NearestVector = -CharacterRight;
			DirectionResult = EBaseDirectionType::Left;
			Debug::Print("Left");
			LookDirection = UKismetMathLibrary::RotateAngleAxis(LookDirection, 90, FVector::UpVector);
		}
	}

	FRotator TargetRot = LookDirection.Rotation();
	DodgeCharacter->SetActorRotation(TargetRot);
}
