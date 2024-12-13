// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSectorWall.generated.h"

UCLASS()
class SCARLETNEXUS_API ABaseSectorWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSectorWall();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY()
	UStaticMeshComponent* StaticMesh;

public:
	UStaticMeshComponent* GetStaticMesh() { return StaticMesh; }
};
