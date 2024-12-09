// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FellowCharacter.h"

void AFellowCharacter::SetWeaponVisibility(bool Visibility)
{
	if (Weapon)
	{
		Weapon->SetVisibility(Visibility, true);
	}

}
