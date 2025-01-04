// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EnemyCharacter/CommonEnemyCharacter.h"
#include "em0700_EnemyCharacter.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API Aem0700_EnemyCharacter : public ACommonEnemyCharacter
{
	GENERATED_BODY()

public:
	Aem0700_EnemyCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* AfterimageEffectComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "SAS")
	UNiagaraSystem* AfterImageEffectSystem = nullptr;

	
	virtual void BeginPlay() override;
};
