// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Character_Kasane.generated.h"

class UDataAsset_InputConfig;
struct FInputActionValue;
struct FGameplayTag;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API ACharacter_Kasane : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	ACharacter_Kasane();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UDataAsset_InputConfig* InputConfig;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnInputMoveTriggered(const FInputActionValue& Value);
	void OnInputLookTriggered(const FInputActionValue& Value);
	void OnAbilityInputTriggered(FGameplayTag InputTag);
};
