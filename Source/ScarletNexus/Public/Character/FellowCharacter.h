// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "FellowCharacter.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
class UCharacterMovementComponent;


/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API AFellowCharacter : public ABaseCharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY( BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* MainBody;

	UPROPERTY( BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* OutLineBody;

	UPROPERTY( BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* Weapon;

	UPROPERTY( BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* OutLineWeapon;

	UPROPERTY( BlueprintReadOnly, Category = "CapsuleComponent")
	UCapsuleComponent* MainCapsule;

	UPROPERTY( BlueprintReadOnly, Category = "CapsuleComponent")
	UCapsuleComponent* HitboxCapsule;

	UPROPERTY( BlueprintReadOnly, Category = "CharacterMovementComponent")
	UCharacterMovementComponent* Movement;

	UFUNCTION(BlueprintCallable, Category = "Visibility")
	void SetWeaponVisibility(bool Visibility);


	virtual void PossessedBy(AController* NewController) override;

	
};
