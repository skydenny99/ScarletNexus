// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TimeControlSubsystem.generated.h"


class ITimeControlInterface;

UENUM(BlueprintType)
enum class ETimeDilationReason : uint8
{
	None = 0,
	SAS_Accel = 1,
	Total = 2,
};
/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_TwoParams(FTimeDilationDelegate, const ETimeDilationReason&, float)

UCLASS()
class SCARLETNEXUS_API UTimeControlSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
protected:

	ETimeDilationReason CurrentTimeDilationReason;
	float CurrentCustomTimeDilation = 1.f;
	
	TMap<FName, float> WorldTimeDilationMap;
	float CurrentWorldTimeDilation;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	FTimeDilationDelegate TimeDilationDelegate;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	UFUNCTION(BlueprintCallable, Category = "TimeControl")
	void SetCustomTimeDilation(ETimeDilationReason Reason, float TimeDilation);
	float GetCurrentCustomTimeDilation() const {return CurrentCustomTimeDilation;};
	ETimeDilationReason GetCurrentTimeDilationReason() const {return CurrentTimeDilationReason;};
	
	UFUNCTION(BlueprintCallable, Category = "TimeControl")
	void SetupWorldTimeDilation(const FName& DilationName, float TimeDilation);

	UFUNCTION(BlueprintCallable, Category = "TimeControl")
	void ReleaseWorldTimeDilation(const FName& DilationName);
};
