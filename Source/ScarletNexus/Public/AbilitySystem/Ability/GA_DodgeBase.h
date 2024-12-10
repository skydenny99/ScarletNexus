// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Ability/GameplayAbilityBase.h"
#include "GA_DodgeBase.generated.h"

class ABaseCharacter;
class UCharacterMovementComponent;
enum class EBaseDirectionType : uint8;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API UGA_DodgeBase : public UGameplayAbilityBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
	TMap<EBaseDirectionType, UAnimMontage*> DodgeMontages;

	UPROPERTY()
	ABaseCharacter* DodgeCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodge")
	FGameplayTagContainer BlockDodgeTags;
	
public:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Dodge")
	virtual void GetCharacterDodgeDirection(EBaseDirectionType& DirectionResult);

	UFUNCTION(BlueprintPure, Category = "Dodge")
	FORCEINLINE ABaseCharacter* GetDodgeCharacter() const { return DodgeCharacter; }
	
};
