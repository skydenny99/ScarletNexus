// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "BaseEnemyCharacter.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
class UCharacterMovementComponent;
class UEnemyCombatComponent;
class UEnemyAttributeSet;
class UWidgetComponent;
class UEnemyUIComponent;

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

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	// UEnemyAttributeSet* EnemyAttributeSet;
	
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Combat", meta = (AllowPrivateAccess = "true"))
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UWidgetComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UWidgetComponent* NoticeComponent;

	UPROPERTY(VisibleDefaultsOnly)
	UWidgetComponent* LockOnComponent;
	
	UPROPERTY(BlueprintReadOnly)
	UEnemyUIComponent* EnemyUIComponent;

	public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;


	virtual FVector GetTargetVector() {return FVector::ZeroVector;}
	
};
