// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/EnemyCharacter/BaseEnemyCharacter.h"
#include "BossEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API ABossEnemyCharacter : public ABaseEnemyCharacter
{
	GENERATED_BODY()

public:
	ABossEnemyCharacter();

	virtual FVector GetTargetVector() override;
	
};
