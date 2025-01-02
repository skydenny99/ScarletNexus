// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EnemyCharacter/BaseEnemyCharacter.h"
#include "CommonEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API ACommonEnemyCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()


	virtual FVector GetTargetVector() override;
	
};
