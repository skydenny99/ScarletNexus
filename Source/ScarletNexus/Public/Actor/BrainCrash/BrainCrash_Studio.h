// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BrainCrash_Studio.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SCARLETNEXUS_API ABrainCrash_Studio : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrainCrash_Studio();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* MainBody;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* OutLineBody;
};
