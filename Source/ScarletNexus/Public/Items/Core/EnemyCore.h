// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCore.generated.h"


class UBoxComponent;
UCLASS()
class SCARLETNEXUS_API AEnemyCore : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyCore();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* MainMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UBoxComponent* CoreCollsionBox;

public:
	FORCEINLINE UBoxComponent* GetCoreCollisionBox() const { return CoreCollsionBox; }
	
};
