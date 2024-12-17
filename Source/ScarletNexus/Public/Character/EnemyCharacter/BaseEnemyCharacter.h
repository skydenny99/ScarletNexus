// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "BaseEnemyCharacter.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
class UCharacterMovementComponent;
class UEnemyCombatComponent;


/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API ABaseEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ABaseEnemyCharacter();
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* MainBody;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CapsuleComponent")
	UCapsuleComponent* MainCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CapsuleComponent")
	UCapsuleComponent* HitboxCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterMovementComponent")
	UCharacterMovementComponent* Movement;


	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Combat", meta = (AllowPrivateAccess = "true"))
	UEnemyCombatComponent* EnemyCombatComponent;

	public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	
};
