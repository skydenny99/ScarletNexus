// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FellowCharacter.h"

#include "BaseDebugHelper.h"

void AFellowCharacter::SetWeaponVisibility(bool Visibility)
{
	if (Weapon)
	{
		Weapon->SetVisibility(Visibility, true);
	}

}

void AFellowCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// Debug::Print(FString::Printf(TEXT("Controller Type: %s"), *NewController->GetActorLabel()),FColor::Red);
}
