// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "BaseCharacter.generated.h"

class UBaseAbilitySystemComponent;
class UDataAsset_StartupBase;
 class UBaseAttributeSet;

UCLASS()
class SCARLETNEXUS_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UDataAsset_StartupBase> StartupData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Time Dilation")
	bool IsAffectedByAccelAbility = true;
	void SetCustomTimeDilation(float TimeDilation) { CustomTimeDilation = TimeDilation; };

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystem")
	UBaseAbilitySystemComponent* BaseAbilitySystemComponent;

	 UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	 UBaseAttributeSet* BaseAttributeSet;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;


	// Combat 인터페이스
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	
public:
	FORCEINLINE UBaseAbilitySystemComponent* GetBaseAbilitySystemComponent() const { return BaseAbilitySystemComponent; }
	FORCEINLINE UBaseAttributeSet* GetBaseAttributeSet() const { return BaseAttributeSet; }

};
