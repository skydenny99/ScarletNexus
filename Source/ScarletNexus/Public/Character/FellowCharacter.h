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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* MainBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* OutLineBody;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* OutLineWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CapsuleComponent")
	UCapsuleComponent* MainCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CapsuleComponent")
	UCapsuleComponent* HitboxCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterMovementComponent")
	UCharacterMovementComponent* Movement;

	UFUNCTION(BlueprintCallable, Category = "Visibility")
	void SetWeaponVisibility(bool Visibility);


	
};
