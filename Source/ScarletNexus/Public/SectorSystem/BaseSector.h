// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseSector.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class ABaseSectorWall;
class UMaterialInterface;
class UBoxComponent;

UCLASS()
class SCARLETNEXUS_API ABaseSector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseSector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* Center;

	UPROPERTY()
	TArray<ABaseSectorWall*> WallArray;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* TriggerBox;

	UPROPERTY(EditDefaultsOnly, Category = "Sector", Meta = (AllowPrivateAccess = "true"))
	UMaterialInterface* WallMaterial;
	
	UPROPERTY(EditDefaultsOnly, Category = "Sector", Meta = (AllowPrivateAccess = "true"))
	float Radius = 400;

	UPROPERTY(EditDefaultsOnly, Category = "Sector", Meta = (AllowPrivateAccess = "true"))
	int32 Divide = 3;
	
	UPROPERTY(VisibleDefaultsOnly)
	TArray<USceneComponent*> SpawnPos;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> Enemy;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> Enemies;
	
	int32 StageNum = 1;
	int StagePosNum[3][3] = {{0,1,2},{3,4,5},{6,7,8}};
	
protected:
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
public:
	UFUNCTION(BlueprintCallable, Category="BaseSector")
	void SpawnWall();

	UFUNCTION()
	void ActivateWall();

	UFUNCTION()
	void UnActivateWall();

	UFUNCTION()
	void SpawnEnemy(const int32 Stage);
	
	UFUNCTION()
	void OnRemoveEnemy(AActor* DestroyedActor);

	UFUNCTION()
	void NextStage();
	
	/*
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
*/

	

};


