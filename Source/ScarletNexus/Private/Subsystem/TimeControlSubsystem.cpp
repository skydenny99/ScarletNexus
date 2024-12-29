// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/TimeControlSubsystem.h"

bool UTimeControlSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return (WorldType == EWorldType::Game) || (WorldType == EWorldType::PIE);
}

void UTimeControlSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	if (const UWorld* World = InWorld.GetWorld())
	{
		
	}
}

void UTimeControlSubsystem::SetCustomTimeDilation(float TimeDilation)
{
	//TimeDilationDelegate.Broadcast()
}
