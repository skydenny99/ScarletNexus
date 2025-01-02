// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "KasaneController.generated.h"

/**
 * 
 */
UCLASS()
class SCARLETNEXUS_API AKasaneController : public APlayerController,  public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	AKasaneController();
	virtual FGenericTeamId GetGenericTeamId() const override;

private:
	FGenericTeamId HeroTeamId;
	
};
