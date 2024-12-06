// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/BaseAnimInstance.h"
#include "BaseFunctionLibrary.h"

bool UBaseAnimInstance::OwnerHasTag(FGameplayTag Tag) const
{
	if (APawn* OwnerPawn = TryGetPawnOwner())
	{
		return UBaseFunctionLibrary::NativeActorHasTag(OwnerPawn, Tag);
	}
	return false;
}
