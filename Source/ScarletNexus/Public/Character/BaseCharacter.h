// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BaseCharacter.generated.h"

class UBaseAbilitySystemComponent;
class UDataAsset_StartupBase;

UCLASS()
class SCARLETNEXUS_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UDataAsset_StartupBase> StartupData;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UBaseAbilitySystemComponent* BaseAbilitySystemComponent;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void PossessedBy(AController* NewController) override;

public:
	FORCEINLINE UBaseAbilitySystemComponent* GetBaseAbilitySystemComponent() const { return BaseAbilitySystemComponent; }


};
