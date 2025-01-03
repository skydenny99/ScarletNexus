// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/FellowCharacter.h"
#include "FellowCharacter_Arashi.generated.h"


class UNiagaraComponent;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API AFellowCharacter_Arashi : public AFellowCharacter
{
	GENERATED_BODY()

public:
	AFellowCharacter_Arashi();
	
	UPROPERTY()
	UNiagaraComponent* AfterimageEffectComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "SAS")
	UNiagaraSystem* AfterImageEffectSystem = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual bool AllowSetTimeDilation(const ETimeDilationReason& Reason) override;

	UFUNCTION(BlueprintCallable)
	void SetArashiAfterEffect(const ETimeDilationReason& Reason, float TimeDilation);
	
	
};


