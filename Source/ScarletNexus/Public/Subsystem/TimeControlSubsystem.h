// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TimeControlSubsystem.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FTimeDilationDelegate, float)

UCLASS()
class SCARLETNEXUS_API UTimeControlSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
protected:
	TMap<FName, float> WorldTimeDilationMap;
	float CurrentWorldTimeDilation;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	FTimeDilationDelegate TimeDilationDelegate;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	
	UFUNCTION(BlueprintCallable, Category = "TimeControl")
	void SetCustomTimeDilation(float TimeDilation);
	
	UFUNCTION(BlueprintCallable, Category = "TimeControl")
	void SetupWorldTimeDilation(const FName& DilationName, float TimeDilation);

	UFUNCTION(BlueprintCallable, Category = "TimeControl")
	void ReleaseWorldTimeDilation(const FName& DilationName);
};
