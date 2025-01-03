// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EnemyCharacter/BaseEnemyCharacter.h"
#include "CommonEnemyCharacter.generated.h"

class AEnemyCore;
/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API ACommonEnemyCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()

public:
	ACommonEnemyCharacter();

protected:
	UPROPERTY()
	UChildActorComponent* EnemyCoreChildComponent;
	
	virtual void BeginPlay() override;
public:

	UFUNCTION(BlueprintCallable, Category="EnemyCore")
	void ActivateEnemyCore(bool bIsActive);
	
	virtual FVector GetTargetVector() override;
	
};
