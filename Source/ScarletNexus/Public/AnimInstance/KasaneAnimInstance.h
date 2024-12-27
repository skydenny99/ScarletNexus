// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstance/CharacterAnimInstance.h"
#include "BaseType/BaseEnumType.h"
#include "KasaneAnimInstance.generated.h"

class ACharacter_Kasane;
DECLARE_DELEGATE(FOnDodgeEnd);
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UKasaneAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	ACharacter_Kasane* OwningKasane;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	int32 JumpCount;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	float VelocityZ;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Locomotion")
	bool bNeedToStop;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Locomotion")
	bool bDoingDodge;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Locomotion")
	EBaseDirectionType DodgeDirection;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	FGameplayTag AttackTag;


public:
	FOnDodgeEnd OnDodgeEnd;
	
	UFUNCTION(BlueprintCallable)
	void Dodge(EBaseDirectionType Direction);

	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	void DodgeEnd();

	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	USkeletalMeshComponent* GetPsychSkeletalMesh() const;
};
