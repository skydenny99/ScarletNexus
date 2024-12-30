// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "BaseType/BaseEnumType.h"
#include "Character/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Character_Kasane.generated.h"


class USASManageComponent;
class UCameraComponent;
class UPsychokinesisComponent;
class USphereComponent;
class UTargetTrackingSpringArmComponent;
class UComboSystemComponent;
struct FInputActionInstance;
class UDataAsset_DirectionInputConfig;
class UDataAsset_InputConfig;
class UKasaneCombatComponent;
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

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UDataAsset_InputConfig* InputConfig;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UDataAsset_DirectionInputConfig* DirectionInputConfig;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UCapsuleComponent* MainCapsule;
	
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UCapsuleComponent* HitboxCapsule;
	
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


	// Combat Component
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, category = "Combat", meta = (AllowPrivateAccess = "true"))
	UKasaneCombatComponent* KasaneCombatComponent;
	
	
	
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
	FORCEINLINE UTargetTrackingSpringArmComponent* GetTargetTrackingComponent() const { return CameraBoom; }

	void ChangeCamera(bool bUseMain = true);
	FORCEINLINE UCameraComponent* GetMainCamera() const { return MainCamera; }
	FORCEINLINE AActor* GetComboDirectCameraActor() const { return ComboDirectCameraActor->GetChildActor(); }


	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	
	
	
};

inline void ACharacter_Kasane::ChangeCamera(bool bUseMain)
{
	auto PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (bUseMain)
		PC->SetViewTargetWithBlend(this, 1.f);
	else
		PC->SetViewTargetWithBlend(ComboDirectCameraActor->GetChildActor(), 1.f);
}

inline void ACharacter_Kasane::BeginPlay()
{
	Super::BeginPlay();
	ComboDirectCameraActor->CreateChildActor();
}
