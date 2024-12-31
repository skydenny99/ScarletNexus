// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "BaseType/BaseEnumType.h"
#include "Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Character_Kasane.generated.h"

class UInventoryComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USASManageComponent;
class UCameraComponent;
class UPsychokinesisComponent;
class USphereComponent;
class UTargetTrackingSpringArmComponent;
class UComboSystemComponent;
struct FInputActionInstance;
class UDataAsset_DirectionInputConfig;
class UDataAsset_InputConfig;
struct FInputActionValue;
struct FGameplayTag;
class UPlayerUIComponent;
class UPlayerUIComponent;

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
	UPROPERTY(VisibleDefaultsOnly, Category="Camera")
	UCameraComponent* MainCamera;
	
	UPROPERTY(VisibleDefaultsOnly, Category="Camera")
	UChildActorComponent* ComboDirectCameraActor;
	
	UPROPERTY(EditAnywhere, Category="Camera")
	UTargetTrackingSpringArmComponent* CameraBoom;
	
	UPROPERTY(EditDefaultsOnly, Category="Battle")
	UComboSystemComponent* ComboSystemComponent;

	UPROPERTY(EditDefaultsOnly, Category="Battle")
	USphereComponent* JustDodgeBoundary;

	UPROPERTY(EditDefaultsOnly, Category="Battle")
	USASManageComponent* SASManageComponent;

	UPROPERTY(EditDefaultsOnly, Category="Psych")
	USphereComponent* PsychBoundary;

	UPROPERTY(EditDefaultsOnly, Category="Psych")
	UPsychokinesisComponent* PsychokinesisComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory")
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	UPlayerUIComponent* PlayerUIComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UDataAsset_InputConfig* InputConfig;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UDataAsset_DirectionInputConfig* DirectionInputConfig;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	void OnInputMoveTriggered(const FInputActionValue& Value);
	void OnInputLookTriggered(const FInputActionValue& Value);
	void OnAbilityInputTriggered(FGameplayTag InputTag);
	void OnSASAbilityInputTriggered(FGameplayTag InputTag);
	void UpdateMovementElapsedTime(const FInputActionInstance& Instance);
	void ResetMovementElapsedTime(const FInputActionValue& Value);
	void OnTargetingInputTriggered(const FInputActionValue& Value);

	//UI
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	virtual UPlayerUIComponent* GetPlayerUIComponent() const override;
	
public:
	void OnAttackInputTriggered(FGameplayTag InputTag, const FInputActionInstance& Instance);
	void OnAttackInputCompleted(FGameplayTag InputTag, const FInputActionInstance& Instance);

private:
	float MovementElapsedTime;
	float MovementTriggeredTime;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input", meta=(AllowPrivateAccess = "true"))
	float DodgeAllowThreshold = 0.15f;
	FTimerHandle DodgeThresholdTimer;


	FRotator OriginRotationRate;
	FRotator FallingRotationRate = FRotator(0.f, 50.f, 0.f);

	UFUNCTION()
	void OnFalling(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);

	uint8 DirectionHistory = static_cast<uint8>(EBaseDirectionType::Max);
	void PushInput(EBaseDirectionType Direction);
	void ClearInputHistory();

	// SAS variables
	UPROPERTY()
	USkeletalMeshComponent* LeftCloneComponent = nullptr;
	UPROPERTY()
	USkeletalMeshComponent* RightCloneComponent = nullptr;
	UPROPERTY()
	UNiagaraComponent* AfterimageEffectComponent = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "SAS")
	UNiagaraSystem* AfterImageEffectSystem = nullptr;
	
public:
	FORCEINLINE uint8 GetDirectionByHistory();

	UFUNCTION(BlueprintCallable)
	void ActivateDash(bool bIsDashing);
	FORCEINLINE float GetMovementElapsedTime() const { return MovementElapsedTime; };
	FORCEINLINE bool NeedToMove() const { return MovementElapsedTime > DodgeAllowThreshold; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE UComboSystemComponent* GetComboSystemComponent() const { return ComboSystemComponent; };
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE UPsychokinesisComponent* GetPsychokinesisComponent() const { return PsychokinesisComponent; };

	UFUNCTION(BlueprintPure)
	FORCEINLINE UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; };

	//UFUNCTION(BlueprintPure)
	//FORCEINLINE UPlayerUIComponent* GetPlayerUIComponent() const { return PlayerUIComponent; };
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE UTargetTrackingSpringArmComponent* GetTargetTrackingComponent() const { return CameraBoom; }

	void ChangeCamera(bool bUseMain = true);
	FORCEINLINE UCameraComponent* GetMainCamera() const { return MainCamera; }
	FORCEINLINE AActor* GetComboDirectCameraActor() const { return ComboDirectCameraActor->GetChildActor(); }


	// SAS functions
	UFUNCTION(BlueprintCallable)
	void ActivateAfterimage(bool InIsActive);
	
	UFUNCTION(BlueprintCallable)
	void ActivateCloneSkeletalMesh(bool InIsActive, int32 InCount = 2);

	// Item Functions
	void OnChangeItemInputTriggered(const FInputActionValue& Value);
};

