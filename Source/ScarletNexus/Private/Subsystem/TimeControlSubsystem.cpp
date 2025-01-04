// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/TimeControlSubsystem.h"

#include "BaseDebugHelper.h"
#include "Kismet/GameplayStatics.h"

bool UTimeControlSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return (WorldType == EWorldType::Game) || (WorldType == EWorldType::PIE);
}

void UTimeControlSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	if (const UWorld* World = InWorld.GetWorld())
	{
		CurrentWorldTimeDilation = 1.f;
	}
}

void UTimeControlSubsystem::SetCustomTimeDilation(ETimeDilationReason Reason, float TimeDilation)
{
	CurrentTimeDilationReason = Reason;
	CurrentCustomTimeDilation = TimeDilation;
	if (TimeDilationDelegate.IsBound())
	{
		TimeDilationDelegate.Broadcast(Reason, TimeDilation);
	}
}

void UTimeControlSubsystem::SetupWorldTimeDilation(const FName& DilationName, float TimeDilation)
{
	if (WorldTimeDilationMap.Contains(DilationName) == false)
	{
		if (CurrentWorldTimeDilation > TimeDilation)
		{
			UGameplayStatics::SetGlobalTimeDilation(GetWorld(), TimeDilation);
			CurrentWorldTimeDilation = TimeDilation;
		}
		WorldTimeDilationMap.Add(DilationName, TimeDilation);
	}
}

void UTimeControlSubsystem::ReleaseWorldTimeDilation(const FName& DilationName)
{
	if (WorldTimeDilationMap.Contains(DilationName))
	{
		WorldTimeDilationMap.Remove(DilationName);
		if (WorldTimeDilationMap.IsEmpty())
		{
			CurrentWorldTimeDilation = 1.f;
		}
		else
		{
			float MinTimeDilation = std::numeric_limits<float>::infinity();
			for (auto Pair : WorldTimeDilationMap)
			{
				if (Pair.Value < MinTimeDilation)
				{
					MinTimeDilation = Pair.Value;
				}
			}
			CurrentWorldTimeDilation = MinTimeDilation;
		}
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), CurrentWorldTimeDilation);
		
	}
}
