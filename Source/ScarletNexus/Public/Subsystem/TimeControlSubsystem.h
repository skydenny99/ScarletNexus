// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TimeControlSubsystem.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FTimeDilationDelegate, AActor*)

UCLASS()
class SCARLETNEXUS_API UTimeControlSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
protected:
	
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	FTimeDilationDelegate TimeDilationDelegate;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	void SetCustomTimeDilation(float TimeDilation);
};
