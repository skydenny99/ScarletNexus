// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystem/TimeControlSubsystem.h"
#include "UObject/Interface.h"
#include "TimeControlInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTimeControlInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SCARLETNEXUS_API ITimeControlInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetCustomTimeDilation(ETimeDilationReason Reason, float TimeDilation) = 0;
};
