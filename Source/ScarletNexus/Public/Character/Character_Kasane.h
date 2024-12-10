// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseType/BaseEnumType.h"
#include "Character/BaseCharacter.h"
#include "Character_Kasane.generated.h"

class UDataAsset_DirectionInputConfig;
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
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UDataAsset_DirectionInputConfig* DirectionInputConfig;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnInputMoveTriggered(const FInputActionValue& Value);
	void OnInputLookTriggered(const FInputActionValue& Value);
	void OnAbilityInputTriggered(FGameplayTag InputTag);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	float DodgeAllowThreshold = 0.15f;
	FTimerHandle DodgeThresholdTimer;


	FRotator OriginRotationRate;
	FRotator FallingRotationRate = FRotator(0.f, 50.f, 0.f);

	UFUNCTION()
	void OnFalling(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);

	uint8 DirectionHistory = static_cast<uint8>(EBaseDirectionType::Max);
	void PushInput(EBaseDirectionType Direction);
	uint8 GetDirectionByHistory();
	void ClearInputHistory();
public:
	uint8 GetDirectionInputHistory() const;

};
