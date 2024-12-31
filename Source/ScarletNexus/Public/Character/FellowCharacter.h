// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "FellowCharacter.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
class UCharacterMovementComponent;
class UFellowCombatComponent;
class UPlayerUIComponent;
class UPawnUIComponent;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API AFellowCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AFellowCharacter();
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* MainBody;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* OutLineBody;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CapsuleComponent")
	UCapsuleComponent* MainCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CapsuleComponent")
	UCapsuleComponent* HitboxCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterMovementComponent")
	UCharacterMovementComponent* Movement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	UPlayerUIComponent* PlayerUIComponent;

	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Combat", meta = (AllowPrivateAccess = "true"))
	UFellowCombatComponent* FellowCombatComponent;

	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UPlayerUIComponent* GetPlayerUIComponent() const override;

public:
	FORCEINLINE UFellowCombatComponent* GetFellowCombatComponent() const { return FellowCombatComponent; }

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	
};
