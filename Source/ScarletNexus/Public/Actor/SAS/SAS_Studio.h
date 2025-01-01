// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SAS_Studio.generated.h"


class USkeletalMeshComponent;


UCLASS()
class SCARLETNEXUS_API ASAS_Studio : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASAS_Studio();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* MainBody;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkeletalMeshData")
	USkeletalMeshComponent* OutLineBody;

};
